/*
Use these for help:
http://www.vtk.org/Wiki/VTK/Examples/Cxx/Visualization/MultipleViewports


*/
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
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkRungeKutta4.h>
#include <vtkStreamTracer.h>
#include <vtkHedgehog.h>
#include <vtkGlyph3D.h>
#include <vtkArrowSource.h>
#include <vtkMaskPoints.h>

int main(int, char *[])
{
  vtkDataSetReader *rdr = vtkDataSetReader::New();
        rdr->SetFileName("proj7.vtk");
        rdr->Update();//Getting File
  int dims[3];
  vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
  rgrid->GetDimensions(dims);

  float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
  float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
  float *Z = (float *) rgrid->GetZCoordinates()->GetVoidPointer(0);

  
   vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();//What handles all the renderer
   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New(); 
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  double xmins[4] = {0,.5,0,.5}, xmaxs[4] = {0.5,1,0.5,1}, ymins[4] = {0,0,.5,.5}, ymaxs[4] = {0.5,0.5,1,1};
//================================================================================/
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(600,600);
  renderer->SetViewport(xmins[0],ymins[0],xmaxs[0],ymaxs[0]);
  //Bottom Left //Isosurface of Hardyglobal// ISO 2.5 & ISO 5.0
    
  vtkContourFilter *cf = vtkContourFilter::New();
  cf->SetNumberOfContours(2);
  cf->SetValue(0, 2.5);
  cf->SetValue(1,5);
  cf->SetInputConnection(rdr->GetOutputPort());
  cf->Update();

  vtkSmartPointer<vtkPolyDataMapper> win1Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  win1Mapper->SetInputConnection(cf->GetOutputPort());
  win1Mapper->SetScalarRange(0,5);
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(win1Mapper);
  renderer->AddActor(actor);
  renderer->ResetCamera();
 
  renderWindow->Render(); //Do I need after each?

//================================================================================/
  vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(renderer1);
  renderer1->SetViewport(xmins[2],ymins[2],xmaxs[2],ymaxs[2]); 

  vtkSmartPointer<vtkPlane> plane1 = vtkSmartPointer<vtkPlane>::New();
      plane1->SetOrigin(0,0,0);
      plane1->SetNormal(1,0,0);
  vtkSmartPointer<vtkPlane> plane2 = vtkSmartPointer<vtkPlane>::New();
      plane2->SetOrigin(0,0,0);
      plane2->SetNormal(0,1,0);
  vtkSmartPointer<vtkPlane> plane3 = vtkSmartPointer<vtkPlane>::New();
      plane3->SetOrigin(5,0,0);
      plane3->SetNormal(0,0,1);

  vtkSmartPointer<vtkCutter> cutter1 = vtkSmartPointer<vtkCutter>::New();
      cutter1->SetCutFunction(plane1);
      cutter1->SetInputConnection(rdr->GetOutputPort());
      cutter1->Update();
  vtkSmartPointer<vtkCutter> cutter2 = vtkSmartPointer<vtkCutter>::New();
      cutter2->SetCutFunction(plane2);
      cutter2->SetInputConnection(rdr->GetOutputPort());
      cutter2->Update();
  vtkSmartPointer<vtkCutter> cutter3 = vtkSmartPointer<vtkCutter>::New();
      cutter3->SetCutFunction(plane3);
      cutter3->SetInputConnection(rdr->GetOutputPort());
      cutter3->Update();
   
  vtkSmartPointer<vtkPolyDataMapper> cut1Window = vtkSmartPointer<vtkPolyDataMapper>::New();
      cut1Window->SetInputConnection( cutter1->GetOutputPort());
      cut1Window->SetScalarRange(0,5);
  vtkSmartPointer<vtkPolyDataMapper> cut2Window = vtkSmartPointer<vtkPolyDataMapper>::New();
      cut2Window->SetInputConnection( cutter2->GetOutputPort());
      cut2Window->SetScalarRange(0,5);
  vtkSmartPointer<vtkPolyDataMapper> cut3Window = vtkSmartPointer<vtkPolyDataMapper>::New();
      cut3Window->SetInputConnection( cutter3->GetOutputPort());
      cut3Window->SetScalarRange(0,5);

  vtkSmartPointer<vtkActor> actorCut1 = vtkSmartPointer<vtkActor>::New();
      actorCut1->GetProperty()->SetLineWidth(2);
      actorCut1->SetMapper(cut1Window);
  vtkSmartPointer<vtkActor> actorCut2 = vtkSmartPointer<vtkActor>::New();
      actorCut2->GetProperty()->SetLineWidth(2);
      actorCut2->SetMapper(cut2Window);
  vtkSmartPointer<vtkActor> actorCut3 = vtkSmartPointer<vtkActor>::New();
      actorCut3->GetProperty()->SetLineWidth(2);
      actorCut3->SetMapper(cut3Window);

  renderer1->AddActor(actorCut1);
  renderer1->AddActor(actorCut2);
  renderer1->AddActor(actorCut3);
  
 //================================================================================/
	vtkDataSet* ds = rdr->GetOutput();
	ds->GetPointData()->SetActiveVectors("grad");
 //================================================================================/

  	vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
	renderWindow->AddRenderer(renderer2);
 	renderer2->SetViewport(xmins[1],ymins[1],xmaxs[1],ymaxs[1]);

	vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();
	arrowSource->SetTipLength(.5);	
	
	vtkSmartPointer<vtkMaskPoints> mask = vtkSmartPointer<vtkMaskPoints>::New();
	mask->SetInputConnection(rdr->GetOutputPort());
	mask->SetMaximumNumberOfPoints(100);
	mask->RandomModeOn();
	
	vtkSmartPointer<vtkGlyph3D> glyph3D = vtkSmartPointer<vtkGlyph3D>::New();
	glyph3D->SetInputConnection(mask->GetOutputPort());
	glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
	glyph3D->SetVectorModeToUseVector();
	
  	vtkSmartPointer<vtkPolyDataMapper> hegMap = vtkSmartPointer<vtkPolyDataMapper>::New();
      		hegMap->SetInputConnection( glyph3D->GetOutputPort());
      		hegMap->SetScalarRange(2,5);
  	vtkSmartPointer<vtkActor> actorHeg = vtkSmartPointer<vtkActor>::New();
		actorHeg->SetMapper(hegMap);

      	renderer2->AddActor(actorHeg);

//================================================================================/
	 vtkSmartPointer<vtkRenderer> renderer3 = vtkSmartPointer<vtkRenderer>::New();
	renderWindow->AddRenderer(renderer3);
	renderer3->SetViewport(xmins[3],ymins[3],xmaxs[3],ymaxs[3]);

	double x[19] = {-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9};
	double y[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double z[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i; i < 19; i++)
	{
	    vtkSmartPointer<vtkStreamTracer> rk4 = vtkSmartPointer<vtkStreamTracer>::New();
	    rk4->SetStartPosition(x[i],y[i],z[i]);
	    rk4->SetIntegratorTypeToRungeKutta4();
	    rk4->SetInterpolatorType(1);
	    rk4->SetInputConnection(rdr->GetOutputPort());
	    rk4->SetMaximumPropagation(40);
	    rk4->SetInitialIntegrationStep(.5);
  	    vtkSmartPointer<vtkPolyDataMapper> rk4Map = vtkSmartPointer<vtkPolyDataMapper>::New();
	    	rk4Map->SetInputConnection( rk4->GetOutputPort());
	    	rk4Map->SetScalarRange(0,6);
	    vtkSmartPointer<vtkActor> rk4Actor = vtkSmartPointer<vtkActor>::New();
	    	rk4Actor->SetMapper(rk4Map);
      	    renderer3->AddActor(rk4Actor);	
	}
/*
  	vtkSmartPointer<vtkStreamTracer> rk4 = vtkSmartPointer<vtkStreamTracer>::New();
	rk4->SetStartPosition(*x,*y,*z);
	//rk4->SetIntegratorTypeToRungeKutta4();
	rk4->SetInterpolatorType(1);
	rk4->SetInputConnection(rdr->GetOutputPort());
	rk4->SetMaximumPropagation(20);
	rk4->SetInitialIntegrationStep(.5);

  	vtkSmartPointer<vtkPolyDataMapper> rk4Map = vtkSmartPointer<vtkPolyDataMapper>::New();
      		rk4Map->SetInputConnection( rk4->GetOutputPort());
      		rk4Map->SetScalarRange(2,5);
  	vtkSmartPointer<vtkActor> rk4Actor = vtkSmartPointer<vtkActor>::New();
		rk4Actor->SetMapper(rk4Map);
*/
      	//renderer3->AddActor(rk4Actor);
//================================================================================/
  //Do not change below 


 renderWindow->Render();
 renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
