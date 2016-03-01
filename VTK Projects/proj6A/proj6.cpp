/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SpecularSpheres.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This examples demonstrates the effect of specular lighting.
//
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"
#include <vtkPNGWriter.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkDataSetReader.h>
#include <vtkContourFilter.h>
#include <vtkRectilinearGrid.h>

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>


// ****************************************************************************
//  Function: GetNumberOfPoints
//
//  Arguments:
//     dims: an array of size 3 with the number of points in X, Y, and Z.
//           2D data sets would have Z=1
//
//  Returns:  the number of points in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfPoints(const int *dims)
{
    // 3D
    //return dims[0]*dims[1]*dims[2];
    // 2D
    return dims[0]*dims[1];
}

// ****************************************************************************
//  Function: GetNumberOfCells
//
//  Arguments:
//
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the number of cells in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfCells(const int *dims)
{
    // 3D
    //return (dims[0]-1)*(dims[1]-1)*(dims[2]-1);
    // 2D
    return (dims[0]-1)*(dims[1]-1);
}


// ****************************************************************************
//  Function: GetPointIndex
//
//  Arguments:
//      idx:  the logical index of a point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the point index
//
// ****************************************************************************

int GetPointIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
    // 2D
    return idx[1]*dims[0]+idx[0];
}


// ****************************************************************************
//  Function: GetCellIndex
//
//  Arguments:
//      idx:  the logical index of a cell.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the cell index
//
// ****************************************************************************

int GetCellIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)+idx[0];
    // 2D
    return idx[1]*(dims[0]-1)+idx[0];
}

// ****************************************************************************
//  Function: GetLogicalPointIndex
//
//  Arguments:
//      idx (output):  the logical index of the point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1] 
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      pointId:  a number between 0 and (GetNumberOfPoints(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalPointIndex(int *idx, int pointId, const int *dims)
{
    // 3D
    // idx[0] = pointId%dim[0];
    // idx[1] = (pointId/dims[0])%dims[1];
    // idx[2] = pointId/(dims[0]*dims[1]);

    // 2D
    idx[0] = pointId%dims[0];
    idx[1] = pointId/dims[0];
}


// ****************************************************************************
//  Function: GetLogicalCellIndex
//
//  Arguments:
//      idx (output):  the logical index of the cell index.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      cellId:  a number between 0 and (GetNumberOfCells(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalCellIndex(int *idx, int cellId, const int *dims)
{
    // 3D
    // idx[0] = cellId%(dims[0]-1);
    // idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
    // idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    idx[0] = cellId%(dims[0]-1);
    idx[1] = cellId/(dims[0]-1);
}


class SegmentList
{
   public:
                   SegmentList() { maxSegments = 10000; segmentIdx = 0; pts = new float[4*maxSegments]; };
     virtual      ~SegmentList() { delete [] pts; };

     void          AddSegment(float X1, float Y1, float X2, float Y2);
     vtkPolyData  *MakePolyData(void);

   protected:
     float        *pts;
     int           maxSegments;
     int           segmentIdx;
};

void
SegmentList::AddSegment(float X1, float Y1, float X2, float Y2)
{
    pts[4*segmentIdx+0] = X1;
    pts[4*segmentIdx+1] = Y1;
    pts[4*segmentIdx+2] = X2;
    pts[4*segmentIdx+3] = Y2;
    segmentIdx++;
}

vtkPolyData *
SegmentList::MakePolyData(void)
{
    int nsegments = segmentIdx;
    int numPoints = 2*(nsegments);
    vtkPoints *vtk_pts = vtkPoints::New();
    vtk_pts->SetNumberOfPoints(numPoints);
    int ptIdx = 0;
    vtkCellArray *lines = vtkCellArray::New();
    lines->EstimateSize(numPoints,2);
    for (int i = 0 ; i < nsegments ; i++)
    {
        double pt[3];
        pt[0] = pts[4*i];
        pt[1] = pts[4*i+1];
        pt[2] = 0.;
        vtk_pts->SetPoint(ptIdx, pt);
        pt[0] = pts[4*i+2];
        pt[1] = pts[4*i+3];
        pt[2] = 0.;
        vtk_pts->SetPoint(ptIdx+1, pt);
        vtkIdType ids[2] = { ptIdx, ptIdx+1 };
        lines->InsertNextCell(2, ids);
        ptIdx += 2;
    }

    vtkPolyData *pd = vtkPolyData::New();
    pd->SetPoints(vtk_pts);
    pd->SetLines(lines);
    lines->Delete();
    vtk_pts->Delete();

    return pd;
}
int caseChoser(float* vbox)
{
	float isovalue = 3.2;
	int Case = 0;
	for(int i = 0 ; i < 4; i++)
	{
//		cout << "vbox[" << i << "]: " << vbox[i] << endl;
		if(vbox[i] >= isovalue)
		{
			Case += pow(2,i);
		}

	}
	return Case;

}
float lerp(float p1, float p2)
{
	float t = 0;
	float isovalue = 3.2;
	//t = (p1 - isovalue)/(p2-p1);//
	t = (isovalue - p1)/(p2-p1);//
	return t;
}
void percLerp(float *percBox, float* LL, float* TR , float* edgePointBox)
	{
			 edgePointBox[0] =  (TR[0] - LL[0])*percBox[0]+LL[0]; 
			 edgePointBox[1] =  (TR[1] - LL[1])*percBox[1]+LL[1];
			 edgePointBox[2] =  (TR[0] - LL[0])*percBox[2]+LL[0]; 
			 edgePointBox[3] =  (TR[1] - LL[1])*percBox[3]+LL[1]; 
		         for(int i = 0; i < 4; i++)
			{		
//				cout << "edgePointBox[" << i <<"]: " << edgePointBox[i] << endl;
			}
	}
int main()
{
    int  i, j;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj6.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    // Add 4 segments that put a frame around your isolines.  This also
    // documents how to use "AddSegment".
    SegmentList sl;
    sl.AddSegment(-10, -10, +10, -10); // Add segment (-10,-10) -> (+10, -10)
    sl.AddSegment(-10, +10, +10, +10);
    sl.AddSegment(-10, -10, -10, +10);
    sl.AddSegment(+10, -10, +10, +10);//These Create box

// YOUR CODE TO GENERATE ISOLINES SHOULD GO HERE!
    int xLocation  = 0;
    int yLocation = 0;
    int offset = dims[0]-1; 
    float percEdgeBox[4];
    float vertScalBox[4];
    float geoPointLoc[4];
    int  mapBox[4];
    float isovalue = 3.2;
    int Case = -1;
    float edgeValues[4] = {0,0,0,0};
    for(i =0; i < dims[1]-1; i++)
	{
		for(j = 0; j < dims[0]-1;j++)
		{
			cout << "\n" << endl;
			int baseX = j;
			int baseY = i;
			int xy[2] =  {baseX,baseY};
			int xy1[2] =  {baseX+1,baseY};
			int xy2[2] =  {baseX,baseY+1};
			int xy3[2] =  {baseX+1,baseY+1};
			float lowerLeft[2] = {X[baseX],Y[baseY]};//X,Y pts
			float topRight[2] = {X[baseX+1],Y[baseY+1]};//X,Y pts
			cout << "LLx: " << lowerLeft[0] << " LLy: " << lowerLeft[1] << endl;
			cout << "TRx: " << topRight[0] << " TRy: " << topRight[1] << endl;
			mapBox[0] = GetPointIndex(xy,dims);//Bottom left
			mapBox[1] = GetPointIndex(xy1,dims);//Bottom right
			mapBox[2] = GetPointIndex(xy2,dims);//Top left
			mapBox[3] = GetPointIndex(xy3,dims);//Top right
			for(int k = 0; k < 4; k++)
			{
				cout <<"mapBox[" << k <<"]: "<< mapBox[k] << endl;		
			}

			vertScalBox[0] = F[mapBox[0]];
			vertScalBox[1] = F[mapBox[1]];
			vertScalBox[2] = F[mapBox[2]];
			vertScalBox[3] = F[mapBox[3]];
			for(int f = 0; f < 4; f++)
			{
				cout << "vertScalBox[" << f <<"]: " << vertScalBox[f] <<endl;	
			}

		  	percEdgeBox[0] = lerp(vertScalBox[0],vertScalBox[1]);//edge 0    //How high up you should go A -> B 0%->100%
		  	percEdgeBox[1] = lerp(vertScalBox[1],vertScalBox[3]);//edge 1
		  	percEdgeBox[2] = lerp(vertScalBox[2],vertScalBox[3]);//edge 2 
		  	percEdgeBox[3] = lerp(vertScalBox[0], vertScalBox[2]);//edge 3
			cout << "percEdgeBox[0]: " << percEdgeBox[0] <<"\npercEdgeBox[1]: " << percEdgeBox[1]
			<< "\npercEdgeBox[2]: " << percEdgeBox[2] << "\npercEdgeBox[3]: " << percEdgeBox[3] << endl;	
			
			Case = caseChoser(vertScalBox);			
			cout <<"case: "<<Case <<endl;	
			percLerp(percEdgeBox,lowerLeft,topRight,edgeValues);
            
            if(Case == 6 || Case == 9)//Ambigous Cases
            {
                if(Case == 6)
                {
                    
                    sl.AddSegment(lowerLeft[0],edgeValues[3],edgeValues[2] ,topRight[1]); // Add segment (-10,-10) -> (+10, -10)
                    sl.AddSegment(edgeValues[0],lowerLeft[1],topRight[0],edgeValues[1]);
                }
                else
                {
                    
                    sl.AddSegment(edgeValues[0],lowerLeft[1],lowerLeft[0],edgeValues[3]);
                    sl.AddSegment(edgeValues[2],topRight[1],topRight[0],edgeValues[1]);
                }
            }
            else
            {//Case 0 and Case 15 means you do nothing
                if(Case == 1 || Case == 14)//Bottom Left
                {
		    sl.AddSegment(lowerLeft[0],edgeValues[3],edgeValues[0],lowerLeft[1]);
                }
                else if(Case == 2 || Case == 13)//Bottom Right
                {
                    sl.AddSegment(edgeValues[0],lowerLeft[1],topRight[0],edgeValues[1]);
                }
                else if(Case == 3 || Case == 12)//Horizontal
                {

                    sl.AddSegment(lowerLeft[0],edgeValues[3],topRight[0],edgeValues[1]);
                }
                else if(Case == 4 || Case == 11)//Top Left
                {
                    sl.AddSegment(lowerLeft[0],edgeValues[3],edgeValues[2],topRight[1]);
                }
                else if(Case == 5 || Case == 10)//Vertical
                {
                    sl.AddSegment(edgeValues[0],lowerLeft[1], edgeValues[2], topRight[1]);	

                }
                else if(Case == 7 || Case == 8)//Top Right	
                {
                    sl.AddSegment(edgeValues[2],topRight[1],topRight[0],edgeValues[1]);
                }
		else{}
            }//end of else



		}//end of first for loop
	}//end of second
    
    vtkPolyData *pd = sl.MakePolyData();

    //This can be useful for debugging
/*
    vtkDataSetWriter *writer = vtkDataSetWriter::New();
    writer->SetFileName("paths.vtk");
    writer->SetInputData(pd);
    writer->Write();
 */

    vtkSmartPointer<vtkDataSetMapper> win1Mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    win1Mapper->SetInputData(pd);
    win1Mapper->SetScalarRange(0, 0.15);

    vtkSmartPointer<vtkActor> win1Actor =
      vtkSmartPointer<vtkActor>::New();
    win1Actor->SetMapper(win1Mapper);

    vtkSmartPointer<vtkRenderer> ren1 =
      vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    ren1->AddActor(win1Actor);
    ren1->SetBackground(0.0, 0.0, 0.0);
    renWin->SetSize(800, 800);

    ren1->GetActiveCamera()->SetFocalPoint(0,0,0);
    ren1->GetActiveCamera()->SetPosition(0,0,50);
    ren1->GetActiveCamera()->SetViewUp(0,1,0);
    ren1->GetActiveCamera()->SetClippingRange(20, 120);
    ren1->GetActiveCamera()->SetDistance(30);

    // This starts the event loop and invokes an initial render.
    //
    iren->Initialize();
    iren->Start();

    pd->Delete();
}
