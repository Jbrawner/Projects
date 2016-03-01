#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDataSetReader.h>
#include <vtkRectilinearGrid.h>
#include <vtkFloatArray.h>



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

// ****************************************************************************
//  Function: EvaluateFieldAtLocation
//
//  Arguments:
//     pt: a two-dimensional location
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     F: a scalar field defined on the mesh.  Its size is dims[0]*dims[1].
//
//   Returns: the interpolated field value. 0 if the location is out of bounds.
//
// ****************************************************************************
float
EvaluateFieldAtLocation(const float *pt, const int *dims, 
                        const float *X, const float *Y, const float *F)
{
    float xPoint = pt[0];
    float yPoint = pt[1];
    int i,j;
    int cellCord[2] = {0,0};

    if(xPoint > X[dims[0]-1] || yPoint > Y[dims[1]-1] || xPoint < X[0] || yPoint < Y[0])
    {
        return 0;
    }
    for(i = 0; i < dims[0]; i++)
    {
        if(xPoint < X[i])
        {
            cellCord[0] = i-1;
//    printf("x: %d",cellCord[0]);
            break;  
        }
        
    }  
    for(j =0; j < dims[1]; j++)
    {
        if(yPoint <  Y[j])
        {
            cellCord[1] = j - 1;
    //      printf("y: %d",cellCord[1]);
            break;
        }
    }
    float scalerFieldValues[4];
    //|X|*Y+X just getting a pixel in a image
    scalerFieldValues[0] = F[dims[0] * cellCord[1] + cellCord[0]];
    scalerFieldValues[1] = F[dims[0] * cellCord[1] + cellCord[0]+1];
    scalerFieldValues[2] = F[dims[0] * (cellCord[1]+1)   + cellCord[0]];
    scalerFieldValues[3] = F[dims[0] * (cellCord[1]+1) + cellCord[0]+1];

    float t1,t2; //t1 for 1 & 2
    float FA,FB,FX;
    t1 = (xPoint - X[cellCord[0]])/(X[cellCord[0]+1] - X[cellCord[0]]);     
    FA = scalerFieldValues[0] + (t1*(scalerFieldValues[1] - scalerFieldValues[0])); 
    FB = scalerFieldValues[2] + (t1*(scalerFieldValues[3] - scalerFieldValues[2])); 
    t2 = (yPoint - Y[cellCord[1]])/(Y[cellCord[1]+1] - Y[cellCord[1]]);
    FX = FA + (t2*(FB-FA)); 

    //printf("\nt1:%f t2:%f",t1,t2);
    //printf("\nFA:%f FB:%f FX:%f\n", FA,FB,FX);
    
        return FX; 
}

void
WriteImage(vtkImageData *img, const char *filename)
{
    std::string full_filename = filename;
    full_filename += ".png";
    vtkPNGWriter *writer = vtkPNGWriter::New();
    writer->SetInputData(img);
    writer->SetFileName(full_filename.c_str());
    writer->Write();
    writer->Delete();
}

vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *image = vtkImageData::New();
    image->SetDimensions(width, height, 1);
    //image->SetWholeExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetUpdateExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetNumberOfScalarComponents(3);
    image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
    //image->AllocateScalars();

    return image;
}

// ****************************************************************************
//  Function: ApplyBlueHotColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0<=F<=1) to a color using the blue 
//     hot color map.
//
//     The blue hot color map has:
//        F=0: (0,0,128) 
//        F=1: (255,255,255) 
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//      
// ****************************************************************************

void
ApplyBlueHotColorMap(float F, unsigned char *RGB)
{
	RGB[0] = (float)F * 255; 	
//	cout << "R: " << RGB << endl;
	RGB[1] = (float)F * 255; 	
//	cout << "G: " << RGB[1] << endl;
	RGB[2] = F*(255-128)+128;
//	cout << "B: " << RGB[2] << endl;
}


// ****************************************************************************
//  Function: ApplyDifferenceColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0<=F<=1) to a color using a divergent colormap
//
//     The divergent color map has:
//        F=0: (0,0,128) 
//        F=0.5: (255,255,255) 
//        F=1: (128, 0, 0)
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//      
// ****************************************************************************
void
ApplyDifferenceColorMap(float F, unsigned char *RGB)
{
	if(F<.5)
	{
	    RGB[0] = F*255*2; 
	    RGB[1] = F*255*2;
	    RGB[2] = 2*F*(255-128) + 128;
	}
	else
	{
	   RGB[0] = 255 - ((F-.5)*255);//correct
	   RGB[1] = 255 - (255*(F-.5))*2;
	   RGB[2] = 255 - (255*(F-.5))*2;
	}
}

// ****************************************************************************
//  Function: ApplyBHSVColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0<=F<=1) to a color using an HSV rainbow colormap
//
//     The rainbow colormap uses a saturation =1.0, value = 1.0, 
//     and interpolates hue from 0 to 360 degrees 
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//      
// ****************************************************************************
void
ApplyHSVColorMap(float F, unsigned char *RGB)
{
	float hue  = 360.0 * F;
	float f,p,q,t,v;
	int i;
	hue = hue/60;
	i = floor(hue);
	f = hue - i;
	v = 255.0;
	t = (1.-(1.-f))*255.0;
	p = 0;
 	q = (1.0-f)*255.0;
	if (i == 0)//0
	{
	    RGB[0] = v;//correct		
	    RGB[1] = t;
	    RGB[2] = p;//need to check	
	}
	if (i==1)//1
	{

	    RGB[0] = q;
	    RGB[1] = v;
	    RGB[2] = p;	
	}
	else if (i == 2)//2
	{

	    RGB[0] = p;		
	    RGB[1] = v;	
	    RGB[2] = t;	
	}
	else if (i == 3)//3
	{

	    RGB[0] = p;		
	    RGB[1] = q;	
	    RGB[2] = v;	
	}
	else if (i == 4)//4
	{

	    RGB[0] = t;		
	    RGB[1] = p;	
	    RGB[2] = v;	
	}
	else if(i == 5)//5
	{

	    RGB[0] = v;		
	    RGB[1] = p;	
	    RGB[2] = q;	
	}
}

int main()
{
    int  i, j;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj3_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    int nx = 500;
    int ny = 500;

    vtkImageData *images[3];
    unsigned char *buffer[3];
    for (i = 0 ; i < 3 ; i++)
    {
        images[i] = NewImage(nx, ny);
        buffer[i] = (unsigned char *) images[i]->GetScalarPointer(0,0,0);
    }

    for (i = 0 ; i < 3*nx*ny ; i++)
        for (j = 0 ; j < 3 ; j++)
            buffer[j][i] = 0;

    for (i = 0 ; i < nx ; i++)
        for (j = 0 ; j < ny ; j++)
        {
            // ITERATE OVER PIXELS
            float pt[2];

	    float tempX = ((float)j/(ny-1));
	    tempX = (float)(tempX*18);
	    pt[1] = (float)tempX - 9;
//	    cout << "tempX: " << pt[0] << endl;	   

	    float tempY	= ((float)i/(nx-1));
	    tempY = (float)(tempY*18);
	    pt[0] = (float)tempY - 9;
//	    cout << "tempY: " << pt[1] << endl;	   

	   float f = EvaluateFieldAtLocation(pt,dims,X,Y,F);
//	   cout << "f: " << f << endl;
		

            float normalizedF = (f-1.2)/(5.02-1.2); //...; see step 5 re 1.2->5.02
            
            // I TAKE OVER HERE
            int offset = 3*(j*nx+i);
            ApplyBlueHotColorMap(normalizedF, buffer[0]+offset);
            ApplyDifferenceColorMap(normalizedF, buffer[1]+offset);
            ApplyHSVColorMap(normalizedF, buffer[2]+offset);
        }

    WriteImage(images[0], "bluehot");
    WriteImage(images[1], "difference");
    WriteImage(images[2], "hsv");
}
