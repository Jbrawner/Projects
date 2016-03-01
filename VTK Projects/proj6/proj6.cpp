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

static int triCase[256][16] = {
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 0: aphilli9 */
{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 1: chatfiel */
{ 0,  1,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 2: chesshir */
{1, 3, 8, 1, 8, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 3: cneugass */
{ 2,  3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 4: cpalk */
{0, 8, 10, 0, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 5: criegler */
{3, 10, 2, 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 6: cworkman */
{1, 2, 10, 1, 9, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},  /* 7: ssane */
{1, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 8: eewing */
{1, 2, 11, 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 9: gmorriso */
{0, 2, 9, 2, 9, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 10: jbayes */
{8, 2, 3, 8, 2, 11, 8, 9, 11, -1, -1, -1, -1, -1, -1, -1},  /*11: Areej Alghamdi (3) 0000 1011*/
{1, 3, 11, 3, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 12: jhorn3 */
{0,8, 10, 0, 1, 10, 1, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 13: jlowen */
{0, 3, 9, 3, 9, 10, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 14: pem */
{8, 9, 11, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 15: kdawes */
{7, 8, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 16: kpinto */
{0, 3, 4, 3, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 17: mcmillan */
{0, 1, 9, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 18: nivaldot */
{1, 3, 7, 1, 4, 7, 1, 4, 9, -1, -1, -1, -1, -1, -1, -1},  /* 19: sgrady2 */
{7, 4, 8, 2, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 20: touermi */
{0, 2, 4, 2, 4, 10, 4, 7, 10, -1, -1, -1, -1, -1, -1, -1},  /* 21: tristanj */
{0, 1, 9, 2, 3, 10, 4, 7, 9, -1, -1, -1, -1, -1, -1, -1},  /* 22: aphilli9 */
{1, 2, 9, 2, 9, 10, 4, 9, 10, 4, 7, 10, -1, -1, -1, -1},  /* 23: chatfiel */
{ 1,  2, 11,  4,  7,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 24: chesshir */
{0, 3, 4, 0, 4, 7, 1, 2, 11, -1, -1, -1, -1, -1, -1, -1},  /* 25: cneugass */
{ 0,  2,  9,  2,  9, 11,  4,  7,  8, -1, -1, -1, -1, -1, -1, -1},  /* 26: cpalk */
{2, 3, 7, 2, 9, 11, 4, 7, 9, 2, 7, 9, -1, -1, -1, -1},  /* 27: criegler */
{10, 3, 11, 4, 8, 10, 1, 11, 3, -1, -1, -1, -1, -1, -1, -1},  /* 28: cworkman */
{ 7,  4, 10,  0,  1,  4,  1,  4, 10,  1, 10, 11, -1, -1, -1, -1},  /*29: David Stevens (4) */
{4, 7, 8, 0, 3, 10, 0, 9, 10, 9, 10, 11, -1, -1, -1, -1},  /* 30: eewing */
{9, 10, 11, 4, 9, 10, 4, 7, 10, -1, -1, -1, -1, -1, -1, -1},  /* 31: gmorriso */
{4, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 32: jbayes */
{0, 3, 8, 4, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 33: jbrawner */
{0, 1, 5, 0, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 34: jhorn3 */
{1, 3, 5, 3, 5, 8, 4, 5, 8, -1, -1, -1, -1, -1, -1, -1},  /* 35: pem */
{2, 3, 10, 4, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 36: jnelson */
{0, 2, 10, 0, 8, 10, 4, 5, 9, -1, -1, -1, -1, -1, -1, -1},  /* 37: kdawes */
{5, 4, 0, 2, 10, 3, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1},  /* 38: kpinto */
{1, 2, 5, 2, 5, 10, 5, 10, 4, 10, 4, 8, -1, -1, -1, -1},  /* 39: mcmillan */
{1, 2, 10, 4, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 40: nivaldot */
{0, 3, 8, 1, 2, 11, 4, 5, 9, -1, -1, -1, -1, -1, -1, -1},  /* 41: sgrady2 */
{0, 2, 4, 2, 5, 11, 2, 4, 5, -1, -1, -1, -1, -1, -1, -1},  /* 42: touermi */
{3, 4, 8, 3, 4, 5, 2, 3, 5, 2, 5, 11, -1, -1, -1, -1},  /* 43: tristanj */
{1, 2, 11, 2, 3, 10, 4, 5, 9, -1, -1, -1, -1, -1, -1, -1},  /* 44: aphilli9 */
{8, 10, 11, 4, 5, 9, 0, 1, 8, 1, 8, 11, -1, -1, -1, -1},  /* 45: chatfiel */
{ 0,  4,  5,  0,  3, 10,  0,  5, 10,  5, 10, 11, -1, -1, -1, -1},  /* 46: chesshir */
{5, 8, 11, 8, 10, 11, 4, 5, 8, -1, -1, -1, -1, -1, -1, -1},  /* 47: cneugass */
{ 5,  7,  9,  7,  8,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 48: cpalk */
{0, 3, 9, 3, 5, 7, 3, 5, 9, -1, -1, -1, -1, -1, -1, -1},  /* 49: criegler */
{0, 8, 7, 0, 7, 1, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},  /* 50: cworkman */
{1, 3, 5, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 51: hang */
{2, 3, 10, 7, 8, 9, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1},  /* 52: eewing */
{5, 7, 9, 2, 7, 10, 0, 2, 9, 6, 7, 9, -1, -1, -1, -1},  /* 53: gmorriso */
{2, 3, 10, 7, 1, 5, 8, 1, 7, 0, 1, 8, -1, -1, -1, -1},  /* 54: jbayes */
{10, 2, 1, 7, 5, 1, 10, 1, 7, -1, -1, -1, -1, -1, -1, -1},  /* 55: jbrawner */
{7, 8, 9, 9, 5, 7, 1, 2, 11, -1, -1, -1, -1, -1, -1, -1},  /* 56: jhorn3 */
{0, 1, 2, 0, 2, 3, 0, 1, 5, 2, 3, 7, -1, -1, -1, -1},  /* 57: jlowen */
{0, 2, 8, 2, 5, 8, 2, 5, 11, 5, 7, 8, -1, -1, -1, -1}  ,  /* 58: jnelson */
{2, 5, 11, 2, 3, 5, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},  /* 59: kdawes */
{9, 5, 8, 8, 7, 5, 11, 10, 3, 1, 3, 11, -1, -1, -1, -1},  /* 60: kpinto */
{0, 1, 9, 5, 7, 11, 7, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 61: mcmillan */
{0, 3, 8, 5, 7, 11, 5, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 62: nivaldot */
{5, 7, 10, 5, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 63: sgrady2 */
{6, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 64: liuly */
{0, 3, 8, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 65: tristanj */
{0, 1, 9, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 66: aphilli9 */
{6, 7, 10, 1, 3, 8, 1, 8, 9, -1, -1, -1, -1, -1, -1, -1},  /* 67: chatfiel */
{ 2,  3,  7,  2,  6,  7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 68: chesshir */
{0, 2, 6, 0, 6, 7, 0, 7, 8, -1, -1, -1, -1, -1, -1, -1},  /* 69: cneugass */
{ 2,  3,  7,  2,  6,  7,  0,  1,  9, -1, -1, -1, -1, -1, -1, -1},  /* 70: cpalk */
{6, 7, 8, 1, 8, 9, 1, 2, 6, 1, 6, 8, -1, -1, -1, -1},  /* 71: criegler */
{1, 2, 11, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 72: cworkman */
{6, 7, 10, 0, 3, 8, 1, 2, 11, -1, -1, -1, -1, -1, -1, -1},  /* 73: liuly */
{0, 2, 9, 2, 9, 11, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1},  /* 74: eewing */
{8, 9, 11, 6, 7, 10, 2, 3, 11, 3, 8, 11, -1, -1, -1, -1},  /* 75: gmorriso */
{7, 3, 1, 7, 1, 11, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},  /* 76: jbayes */
{7, 1, 11, 7, 6, 11, 0, 8, 1, 1, 8, 7, -1, -1, -1, -1},  /* 77: jbrawner */
{0, 9, 11, 0, 3, 7, 0, 7, 11, 6, 7, 11, -1, -1, -1, -1},  /* 78: jhorn3 */
{8, 9, 11, 7, 8, 11, 6, 7, 11, -1, -1, -1, -1, -1, -1, -1},  /*79: Stephanie Labasan (3) */
{4, 8, 6, 10, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}  ,  /* 80: jnelson */
{0, 3, 6, 0, 4, 6, 3, 6, 10, -1, -1, -1, -1, -1, -1, -1},  /* 81: kdawes */
{4, 8, 6, 0, 1, 9, 8, 10, 6, -1, -1, -1, -1, -1, -1, -1},  /* 82: kpinto */
{1, 3, 9, 3, 4, 9, 3, 4, 10, 4, 6, 10, -1, -1, -1, -1},  /* 83: mcmillan */
{3, 4, 8, 2, 3, 4, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},  /* 84: nivaldot */
{0, 2, 4, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 85: sgrady2 */
{2, 4, 6, 0, 1, 9, 3, 4, 8, 2, 3, 4, -1, -1, -1, -1},  /* 86: touermi */
{2, 4, 6, 1, 2, 4, 1, 4, 9, -1, -1, -1, -1, -1, -1, -1},  /* 87: tristanj */
{1, 2, 11, 4, 7, 8, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1},  /* 88: aphilli9 */
{1, 2, 11, 0, 3, 10, 0, 6, 10, 0, 4, 6, -1, -1, -1, -1},  /* 89: chatfiel */
{ 8,  4, 10, 10,  4,  6,  2,  0,  9,  9,  2, 11, -1, -1, -1, -1},  /* 90: chesshir */
{3, 9, 11, 2, 3, 11, 3, 6, 10, 3, 4, 10, 3, 4, 9, -1},  /* 91: cneugass */
{ 1,  3,  8,  1,  6, 11,  1,  6,  8,  4,  6,  8, -1, -1, -1, -1},  /* 92: cpalk */
{0, 4, 6, 0, 1, 11, 0, 6, 11, -1, -1, -1, -1, -1, -1, -1},  /* 93: criegler */
{3, 9, 11, 3, 4, 8, 3, 0, 9, 3, 4, 6, 3, 6, 11, -1},  /* 94: cworkman */
{4, 6, 11, 4, 9, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 95: pem */
{4, 5, 9, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 96: roba */
{0, 3, 8, 4, 5, 9, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1},  /* 97: gmorriso */
{10, 6, 7, 0, 1, 5, 0, 4, 5, -1, -1, -1, -1, -1, -1, -1},  /* 98: jbayes */
{3, 1, 5, 4, 3, 5, 7, 6, 10, 8, 3, 4, -1, -1, -1, -1},  /* 99: jbrawner */
{4, 5, 9, 2, 3, 7, 2, 6, 7, -1, -1, -1, -1, -1, -1, -1},  /* 100: jhorn3 */
{0, 2, 9, 4, 7, 8, 4, 5, 6, -1, -1, -1, -1, -1, -1, -1},  /* 101: jlowen */
{0, 1, 5, 3, 6, 7, 2, 3, 6, 0, 4, 5, -1, -1, -1, -1} ,  /* 102: jnelson */
{1, 2, 8, 1, 8, 5, 2, 6, 8, 4, 5, 8, 7, 8, 6, -1},  /* 103: kdawes */
{4, 5, 9, 6, 7, 10, 1, 2, 11, -1, -1, -1, -1, -1, -1, -1},  /* 104: kpinto */
{0, 1, 9, 2, 3, 10, 4, 7, 8, 5, 6, 11, -1, -1, -1, -1},  /* 105: mcmillan */
{0, 2, 4, 2, 4, 5, 2, 5, 10, 6, 7, 11, -1, -1, -1, -1},  /* 106: nivaldot */
{2, 3, 5, 2, 5, 11, 3, 4, 5, 3, 4, 8, 6, 7, 10, -1},  /* 107: sgrady2 */
{4, 5, 9, 1, 6, 11, 1, 6, 7, 1, 3, 7, -1, -1, -1, -1},  /* 108: touermi */
{0, 7, 8, 0, 1, 7, 1, 6, 7, 0, 6, 7, 4, 5, 9, -1},  /* 109: tristanj */
{0, 1, 9, 1, 2, 11, 2, 3, 10, 4, 5, 9, 6, 7, 10, -1},  /* 110: aphilli9 */
{4, 5, 11, 6, 7, 11, 4, 8, 11, 7, 8, 11, -1, -1, -1, -1},  /* 111: chatfiel */
{ 8,  9, 10,  9,  5,  6,  9,  6, 10, -1, -1, -1, -1, -1, -1, -1},  /* 112: chesshir */
{0, 5, 6, 0, 5, 9, 0, 3, 6, 3, 6, 10, -1, -1, -1, -1},  /* 113: cneugass */
{ 0,  1,  5,  5,  6, 10,  0,  5, 10,  0,  8, 10, -1, -1, -1, -1},  /* 114: cpalk */
{3, 5, 6, 3, 6, 10, 1, 3, 5, -1, -1, -1, -1, -1, -1, -1},  /* 115: criegler */
{ 2,  8,  9,  2,  3,  9,  2,  5,  9,  2,  5,  6, -1, -1, -1, -1},  /* 116: bishara */
{0, 2, 9, 2, 5, 9, 2, 5, 6, -1, -1, -1, -1, -1, -1, -1},  /* 117: josh */
{ 0,  3,  8,  1,  2,  5,  2,  5,  6, -1, -1, -1, -1, -1, -1, -1},  /* 118: annag */
{1, 2, 6, 1, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 119: gmorriso */
{10, 9, 5, 1, 7, 11, 5, 6, 10, 8, 9, 10, -1, -1, -1, -1},  /* 120: jbayes */
{3, 0, 10, 2, 11, 1, 6, 5, 9, 0, 9, 6, 6, 10, 0, -1},  /* 121: jbrawner */
{0, 2, 5, 2, 5, 11, 5, 6, 10, 5, 8, 10, 0, 5, 8, -1},  /* 122: jhorn3 */
{2, 3, 10, 5, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 123: jlowen */
{3, 8, 6, 9, 8, 6, 9, 5, 6, 1, 3, 6, -1, -1, -1, -1} ,  /* 124: jnelson */
{0, 1, 11, 0, 5, 6, 0, 5, 9, 0, 6, 11, -1, -1, -1, -1},  /* 125: kdawes */
{11, 5, 6, 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 126: kpinto */
{5, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 127: mcmillan */
{ 5,  6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 128: bishara */
{0, 3, 8, 5, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 129: sgrady2 */
{0, 1, 9, 5, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 130: touermi */
{5, 6, 11, 1, 3, 8, 1, 3, 9, -1, -1, -1, -1, -1, -1, -1},  /* 131: tristanj */
{2, 3, 10, 5, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 132: aphilli9 */
{5, 6, 11, 0, 2, 10, 0, 8, 10, -1, -1, -1, -1, -1, -1, -1},  /* 133: chatfiel */
{ 0,  1,  9,  5,  6, 11,  2,  3, 10, -1, -1, -1, -1, -1, -1, -1},  /* 134: chesshir */
{5, 6, 11, 2, 9, 10, 8, 9, 10, 1, 2, 9, -1, -1, -1, -1},  /* 135: cneugass */
{ 1,  2,  6,  1,  5,  6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 136: cpalk */
{0, 3, 8, 1, 2, 6, 1, 5, 6, -1, -1, -1, -1, -1, -1, -1},  /* 137: criegler */
{9, 5, 6, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},  /* 138: cworkman */
{ 1,  2,  9,  2,  9, 10,  9, 10,  8, -1, -1, -1, -1, -1, -1, -1},  /* 139: annag */
{1,     3,      5,      3,      6,      10,     3,      5,      6, -1, -1, -1, -1, -1, -1, -1},  /*140: James Kress (3) */
{0, 1, 5, 0, 8, 10, 5, 6, 10, 0, 5, 10, -1, -1, -1, -1},  /* 141: gmorriso */
{0, 5, 9, 0, 5, 6, 0, 3, 6, 3, 6, 10, -1, -1, -1, -1},  /* 142: liuly */
{6, 9, 5, 8, 9, 10, 10, 9, 6, -1, -1, -1, -1, -1, -1, -1},  /* 143: jbrawner */
{4, 7, 8, 5, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 144: jhorn3 */
{5, 6, 11, 0, 3, 4, 3, 4, 7, -1, -1, -1, -1, -1, -1, -1},  /* 145: jlowen */
{0, 1, 9, 4, 7, 8, 5, 6, 11, -1, -1, -1, -1, -1, -1, -1} ,  /* 146: jnelson */
{1, 3, 7, 5, 6, 11, 1, 7, 9, 4, 7, 9, -1, -1, -1, -1},  /* 147: kdawes */
{7, 8, 4, 11, 5, 6, 2, 3, 10, -1, -1, -1, -1, -1, -1, -1},  /* 148: kpinto */
{0, 2, 4, 2, 4, 5, 2, 5, 11, 7, 6, 10, -1, -1, -1, -1},  /* 149: mcmillan */
{0, 1, 9, 2, 3, 11, 4, 7, 8, 5, 6, 10, -1, -1, -1, -1},  /* 150: nivaldot */
{1, 2, 9, 2, 9, 10, 4, 7, 10, 4, 9, 10, 5, 6, 11, -1},  /* 151: sgrady2 */
{1, 2, 6, 1, 5, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},  /* 152: touermi */
{0, 3, 4, 3, 4, 7, 1, 2, 5, 2, 5, 6, -1, -1, -1, -1},  /* 153: tristanj */
{0, 1, 9, 1, 2, 11, 4, 7, 8, 5, 6, 11, -1, -1, -1, -1},  /* 154: aphilli9 */
{5, 6, 9, 4, 7, 9, 2, 3, 9, 2, 6, 9, 3, 7, 9, -1},  /* 155: chatfiel */
{ 8,  4,  7,  3,  1,  5,  3, 10,  5,  5, 10,  6, -1, -1, -1, -1},  /* 156: chesshir */
{5, 6, 10, 4, 7, 10, 0, 4, 10, 1, 5, 10, 0, 1, 10, -1},  /* 157: cneugass */
{ 4,  7,  8,  0,  5,  6,  0,  5,  9,  0,  3,  6,  3,  6, 10, -1},  /* 158: cpalk */
{5, 6, 9, 6, 9, 10, 4, 7, 9, 7, 9, 10, -1, -1, -1, -1},  /* 159: criegler */
{4, 9, 11, 6, 4, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 160: cworkman */
{0, 3, 8, 4, 6, 11, 4, 9, 11, -1, -1, -1, -1, -1, -1, -1},  /*161: Monisha Balireddi (3) */
{0, 1, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},  /* 162: hang */
{4, 6, 8, 1, 3, 8, 1, 6, 11, 1, 6, 8, -1, -1, -1, -1},  /* 163: gmorriso */
{6, 11, 4, 9, 11, 4, 10, 2, 3, -1, -1, -1, -1, -1, -1, -1},  /* 164: jbayes */
{10, 2, 8, 8, 2, 0, 6, 11, 4, 4, 11, 9, -1, -1, -1, -1},  /* 165: jbrawner */
{2, 3, 10, 0, 1, 6, 1, 6, 11, 0, 4, 6, -1, -1, -1, -1},  /* 166: jhorn3 */
{1, 2, 11, 4, 6, 8, 6, 8, 10, -1, -1, -1, -1, -1, -1, -1},  /* 167: jlowen */
{1, 2, 4, 1, 4, 9, 2, 4, 6, -1,-1, -1, -1, -1, -1, -1} ,  /* 168: jnelson */
{0, 3, 8, 1, 2, 9, 2, 4, 6, 2, 4, 9, -1, -1, -1, -1},  /* 169: kdawes */
{0, 2, 4, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 170: kpinto */
{3, 4, 8, 2, 3, 4, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},  /* 171: mcmillan */
{1, 3, 9, 3, 4, 9, 3, 4, 11, 4, 6, 11, -1, -1, -1, -1},  /* 172: nivaldot */
{0, 1, 8, 1, 4, 6, 1, 4, 9, 1, 6, 10, 1, 8, 10, -1},  /* 173: sgrady2 */
{0, 4, 6, 0, 3, 6, 3, 6, 10, -1, -1, -1, -1, -1, -1, -1},  /* 174: touermi */
{4, 6, 8, 6, 8, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 175: tristanj */
{ 8,  9, 11,  6,  8, 11,  6,  7,  8, -1, -1, -1, -1, -1, -1, -1},  /* 176: bishara */
{0, 3, 7, 0, 9, 11, 6, 7, 11, 0, 7, 11, -1, -1, -1, -1},  /* 177: chatfiel */
{ 0,  1,  8,  1,  7,  8,  1,  7, 11,  7, 11,  6, -1, -1, -1, -1},  /* 178: chesshir */
{6, 7, 11, 1, 3, 7, 1, 7, 11, -1, -1, -1, -1, -1, -1, -1},  /* 179: cneugass */
{ 2,  3, 10,  6,  7,  8,  6,  8, 11,  8,  9, 11, -1, -1, -1, -1},  /* 180: cpalk */
{0, 2, 7, 2, 7, 10, 0, 7, 9, 6, 7, 11, 7, 9, 11, -1},  /* 181: criegler */
{2, 3, 10, 0, 1, 8, 6, 7, 11, 1, 8, 7, 1, 11, 7, -1},  /* 182: cworkman */
{1, 2, 10, 1, 6, 11, 1, 6, 7, 1, 7, 10, -1, -1, -1, -1},  /* 183: hang */
{6, 7, 8, 1, 2, 6, 1, 6, 8, 1, 8, 9, -1, -1, -1, -1},  /* 184: liuly */
{1, 2, 9, 0, 3, 9, 3, 7, 9, 6, 7, 9, 2, 6, 9, -1},  /* 185: gmorriso */
{0, 8, 7, 6, 7, 0, 2, 0, 6, -1, -1, -1, -1, -1, -1, -1},  /* 186: jbayes */
{7, 3, 2, 7, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 187: jbrawner */
{1, 3, 6, 1, 6, 9, 6, 8, 9, 6, 7, 8, 3, 6, 10 , -1},  /* 188: jhorn3 */
{0, 1, 9, 6, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 189: jlowen */
{0, 3, 10, 0, 6, 7, 0, 6, 10, 0, 8, 7, -1, -1, -1, -1} ,  /* 190: jnelson */
{6, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 191: kdawes */
{11, 5, 10, 5, 7, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 192: kpinto */
{0, 3, 8, 5, 7, 10, 5, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 193: mcmillan */
{0, 1, 9, 5, 7, 10, 7, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 194: nivaldot */
{1, 3, 8, 1, 8, 9, 5, 7, 11, 7, 10, 11, -1, -1, -1, -1},  /* 195: sgrady2 */
{3, 5, 7, 2, 3, 5, 2, 5, 11, -1, -1, -1, -1, -1, -1, -1},  /* 196: touermi */
{0, 2, 8, 2, 5, 8, 5, 7, 8, 2, 5, 11, -1, -1, -1, -1},  /* 197: tristanj */
{0, 1, 9, 2, 3, 10, 7, 6, 10, 5, 6, 11, -1, -1, -1, -1},  /* 198: aphilli9 */
{2, 5, 11, 1, 2, 9, 2, 5, 7, 2, 7, 8, 2, 8, 9, -1},  /* 199: chatfiel */
{ 1,  5,  7,  1,  2, 10,  7, 10,  1, -1, -1, -1, -1, -1, -1, -1},  /* 200: chesshir */
{0, 3, 8, 1, 5, 7, 1, 2, 7, 2, 7, 10, -1, -1, -1, -1},  /* 201: cneugass */
{ 0,  2,  9,  2,  7,  9,  2,  7, 10,  5,  7,  9, -1, -1, -1, -1},  /* 202: cpalk */
{2, 3, 8, 2, 5, 9, 2, 5, 7, 2, 7, 10, 2, 8, 9, -1},  /* 203: criegler */
{5, 7, 3, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 204: cworkman */
{1, 5, 7, 0, 7, 8, 0, 1, 7, -1, -1, -1, -1, -1, -1, -1},  /* 205: ssane */
{ 3,  5,  7,  0,  3,  5,  0,  5,  9, -1, -1, -1, -1, -1, -1, -1},  /* 206: bishara */
{5, 7, 9, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 207: gmorriso */
{8, 10, 11, 8, 5, 11, 8, 5, 4, -1, -1, -1, -1, -1, -1, -1},  /* 208: jbayes */
{3, 0, 10, 5, 11, 10, 4, 5, 0, 10, 0, 5, -1, -1, -1, -1},  /* 209: jbrawner */
{0, 1, 9, 4, 5, 11, 4, 8, 11, 8, 10, 11, -1, -1, -1, -1},  /* 210: jhorn3 */
{4, 5, 9, 1, 3, 11, 3, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 211: jlowen */
{2, 3, 5, 2, 5, 11, 3, 4, 5, 3, 4, 8,  -1, -1, -1, -1} ,  /* 212: jnelson */
{0, 2, 4, 2, 4, 5, 2, 5, 11, -1, -1, -1, -1, -1, -1, -1},  /* 213: kdawes */
{3, 5, 8, 2, 3, 11, 0, 1, 9, 4, 5, 8, 3, 5, 11, -1},  /* 214: kpinto */
{1, 2, 11, 1, 5, 11, 1, 5, 9, 4, 5, 9, -1, -1, -1, -1},  /* 215: mcmillan */
{1, 2, 5, 2, 5, 11, 4, 5, 11, 4, 8, 11, -1, -1, -1, -1},  /* 216: nivaldot */
{0, 3, 10, 0, 4, 10, 1, 2, 10, 1, 5, 10, 4, 5, 10, -1},  /* 217: sgrady2 */
{2, 5, 10, 0, 5, 9, 0, 2, 5, 4, 5, 8, 5, 8, 10, -1},  /* 218: touermi */
{4, 5, 9, 2, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 219: tristanj */
{1,     3,      5,      4,      5,      8,      3,      8,      5, -1, -1, -1, -1, -1, -1, -1},  /*220: James Kress (3) */
{0, 1, 5, 0, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 221: chatfiel */
{0, 5, 9, 0, 3, 5, 4, 5, 8, 3, 5, 8, -1, -1, -1, -1},  /* 222: hang */
{4, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 223: cneugass */
{ 4,  7, 10,  9, 10, 11,  4,  9, 10, -1, -1, -1, -1, -1, -1, -1},  /* 224: cpalk */
{0, 3, 8, 9, 10, 11, 4, 7, 9, 7, 9, 10, -1, -1, -1, -1},  /* 225: criegler */
{11, 10, 1, 1, 10, 4, 1, 0, 4, 4, 7, 10, -1, -1, -1, -1},  /* 226: cworkman */
{ 4,  7,  8,  1,  3, 10,  1, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 227: bishara */
{3, 4, 7, 2, 3, 4, 2, 4, 9, 2, 9, 11, -1, -1, -1, -1},  /* 228: josh */
{7, 9, 11, 0, 7, 8, 0, 2, 7, 4, 7, 9, 2, 7, 11, -1},  /* 229: gmorriso */
{11, 2, 3, 11, 1, 0, 11, 7, 3, 11, 4, 7, 11, 4, 0, -1},  /* 230: jbayes */
{2, 1, 11, 7, 4, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 231: jbrawner */
{1, 2, 9, 4, 7, 10, 4, 9, 10, 2, 9, 10, -1, -1, -1, -1},  /* 232: jhorn3 */
{0, 1, 9, 2, 3, 10, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},  /* 233: jlowen */
{0, 2, 4, 2, 4, 10, 4, 7, 10, -1, -1, -1, -1, -1, -1, -1} ,  /* 234: jnelson */
{2, 4, 10, 2, 3, 4, 3, 4, 8, 4, 7, 10, -1, -1, -1, -1},  /* 235: kdawes */
{1, 4, 9, 1, 3, 7, 1, 4, 7, -1, -1, -1, -1, -1, -1, -1},  /* 236: kpinto */
{0, 1, 9, 0, 4, 9, 0, 4, 8, 4, 7, 8, -1, -1, -1, -1},  /* 237: mcmillan */
{0, 3, 4, 3, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 238: nivaldot */
{4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 239: sgrady2 */
{8, 9, 11, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 240: touermi */
{0, 3, 9, 3, 9, 10, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},  /* 241: tristanj */
{ 0,  1, 11,  0, 11, 10,  0, 10,  8, -1, -1, -1, -1, -1, -1, -1},  /*242: Brandon Hildreth (3)  1111 0010*/
{1, 3, 11, 3, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 243: chatfiel */
{ 8,  9, 11,  2,  3,  8,  2,  8, 11, -1, -1, -1, -1, -1, -1, -1},  /* 244: chesshir */
{2, 9, 11, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 245: cneugass */
{ 0,  1,  8,  2,  3,  8,  1,  8, 11,  2,  8, 11, -1, -1, -1, -1},  /* 246: cpalk */
{1, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 247: criegler */
{8, 9, 10, 9, 1, 10, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},  /* 248: cworkman */
{0, 1, 9, 2, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 249: josh */
{0, 2, 10, 0, 8, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /*250: Paul Elliott (2) */
{2, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 251: gmorriso */
{1, 3, 8, 1, 8, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 252: jbayes */
{0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 253: jbrawner */
{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 254: pem */
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},  /* 255: jlowen */
};

class TriangleList
{
   public:
                   TriangleList() { maxTriangles = 1000000; triangleIdx = 0; pts = new float[4*maxTriangles]; };
     virtual      ~TriangleList() { delete [] pts; };

     inline void          AddTriangle(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float X3, float Y3, float Z3)
     {
         if (triangleIdx >= maxTriangles)
         {
             cerr << "No room for more triangles!" << endl;
             return;
         }
     
         pts[9*triangleIdx+0] = X1;
         pts[9*triangleIdx+1] = Y1;
         pts[9*triangleIdx+2] = Z1;
         pts[9*triangleIdx+3] = X2;
         pts[9*triangleIdx+4] = Y2;
         pts[9*triangleIdx+5] = Z2;
         pts[9*triangleIdx+6] = X3;
         pts[9*triangleIdx+7] = Y3;
         pts[9*triangleIdx+8] = Z3;
         triangleIdx++;
     };

     inline vtkPolyData  *MakePolyData(void)
     {
         int ntriangles = triangleIdx;
         int numPoints = 3*(ntriangles);
         vtkPoints *vtk_pts = vtkPoints::New();
         vtk_pts->SetNumberOfPoints(numPoints);
         int ptIdx = 0;
         vtkCellArray *tris = vtkCellArray::New();
         tris->EstimateSize(numPoints,3);
         for (int i = 0 ; i < ntriangles ; i++)
         {
             double pt[3];
             pt[0] = pts[9*i+0];
             pt[1] = pts[9*i+1];
             pt[2] = pts[9*i+2];
             vtk_pts->SetPoint(ptIdx, pt);
             pt[0] = pts[9*i+3];
             pt[1] = pts[9*i+4];
             pt[2] = pts[9*i+5];
             vtk_pts->SetPoint(ptIdx+1, pt);
             pt[0] = pts[9*i+6];
             pt[1] = pts[9*i+7];
             pt[2] = pts[9*i+8];
             vtk_pts->SetPoint(ptIdx+2, pt);
             vtkIdType ids[3] = { ptIdx, ptIdx+1, ptIdx+2 };
             tris->InsertNextCell(3, ids);
             ptIdx += 3;
         }
     
         vtkPolyData *pd = vtkPolyData::New();
         pd->SetPoints(vtk_pts);
         pd->SetPolys(tris);
         tris->Delete();
         vtk_pts->Delete();
     
         return pd;
     };
     
   protected:
     float        *pts;
     int           maxTriangles;
     int           triangleIdx;
};

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
    return dims[0]*dims[1]*dims[2];
    // 2D
    //return dims[0]*dims[1];
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
    return (dims[0]-1)*(dims[1]-1)*(dims[2]-1);
    // 2D
    //return (dims[0]-1)*(dims[1]-1);
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
    return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
    // 2D
    //return idx[1]*dims[0]+idx[0];
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
    return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)+idx[0];
    // 2D
    //return idx[1]*(dims[0]-1)+idx[0];
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
     idx[0] = pointId%dims[0];
     idx[1] = (pointId/dims[0])%dims[1];
     idx[2] = pointId/(dims[0]*dims[1]);

    // 2D
    //idx[0] = pointId%dims[0];
    //idx[1] = pointId/dims[0];
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
     idx[0] = cellId%(dims[0]-1);
     idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
     idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    //idx[0] = cellId%(dims[0]-1);
    //idx[1] = cellId/(dims[0]-1);
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
	for(int i = 0 ; i < 8; i++)
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
void percLerp(float *percBox, float* LLL, float* LTR , float* TLL, float* TTR, float* edgePointBox)
	{
			//Bottom Square
			 edgePointBox[0] =  (LTR[0] - LLL[0])*percBox[0]+LLL[0]; 
			 edgePointBox[1] =  (LTR[1] - LLL[1])*percBox[1]+LLL[1];
			 edgePointBox[2] =  (LTR[0] - LLL[0])*percBox[2]+LLL[0]; 
			 edgePointBox[3] =  (LTR[1] - LLL[1])*percBox[3]+LLL[1]; 
			//Top Square
			 edgePointBox[4] =  (TTR[0] - TLL[0])*percBox[4]+TLL[0]; 
			 edgePointBox[5] =  (TTR[1] - TLL[1])*percBox[5]+TLL[1]; 
			 edgePointBox[6] =  (TTR[0] - TLL[0])*percBox[6]+TLL[0]; 
			 edgePointBox[7] =  (TTR[1] - TLL[1])*percBox[7]+TLL[1]; 
			//Side Edges
			 edgePointBox[8] =  (TLL[2] - LLL[2])*percBox[8]+LLL[2]; 
			 edgePointBox[9] =  (TTR[2] - LTR[2])*percBox[9]+LTR[2]; 
			 edgePointBox[10] =  (TLL[2] - LLL[2])*percBox[10]+LLL[2]; 
			 edgePointBox[11] =  (TTR[2] - LTR[2])*percBox[11]+LTR[2]; 
				
		         for(int i = 0; i < 4; i++)
			{		
//				cout << "edgePointBox[" << i <<"]: " << edgePointBox[i] << endl;
			}
	}
int main()
{
    int  i, j,z;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj6B.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *Z = (float *) rgrid->GetZCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    // Add 4 segments that put a frame around your isolines.  This also
    // documents how to use "AddSegment".
    SegmentList sl;
    TriangleList tl;
// YOUR CODE TO GENERATE ISOLINES SHOULD GO HERE!
    int xLocation  = 0;
    int yLocation = 0;
    int offset = dims[0]-1; 
    float percEdgeBox[12];
    float vertScalBox[8];
    float geoPointLoc[8];
    int  mapBox[8];
    float isovalue = 3.2;
    int Case = -1;
    float edgeValues[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
for(z =0; z < dims[2]-1; z++)
    {
    for(i =0; i < dims[1]-1; i++)
	{
		for(j = 0; j < dims[0]-1;j++)
		{
			//cout << "\n" << endl;
			int baseX = j;
			int baseY = i;
			int baseZ = z;
			int xy[3]  =  {baseX,baseY,baseZ};//v0
			int xy1[3] =  {baseX+1,baseY,baseZ};//v1
			int xy2[3] =  {baseX,baseY+1,baseZ};//v2
			int xy3[3] =  {baseX+1,baseY+1,baseZ};//v3
			int xy4[3] =  {baseX,baseY,baseZ+1};//v4
			int xy5[3] =  {baseX+1,baseY,baseZ+1};//v5
			int xy6[3] =  {baseX,baseY+1,baseZ+1};//v6
			int xy7[3] =  {baseX+1,baseY+1,baseZ+1};//v7
			float lowerLeft[3] = {X[baseX],Y[baseY],Z[baseZ]};//X,Y,Z pt
			float topRight[3] = {X[baseX+1],Y[baseY+1],Z[baseZ]};//X,Y,Z pt
			float upperLowerLeft[3] = {X[baseX],Y[baseY],Z[baseZ+1]};//X,Y,Z pt
			float upperTopRight[3] = {X[baseX+1],Y[baseY+1],Z[baseZ+1]};//X,Y,Z pt
			//cout << "LLx: " << lowerLeft[0] << " LLy: " << lowerLeft[1] << endl;
			//cout << "TRx: " << topRight[0] << " TRy: " << topRight[1] << endl;
			mapBox[0] = GetPointIndex(xy,dims);//Lower Bottom left
			mapBox[1] = GetPointIndex(xy1,dims);//Lower Bottom right
			mapBox[2] = GetPointIndex(xy2,dims);//Lower Top left
			mapBox[3] = GetPointIndex(xy3,dims);//Lower Top right
			mapBox[4] = GetPointIndex(xy4,dims);//Top Bottom left
			mapBox[5] = GetPointIndex(xy5,dims);//Top Bottom right
			mapBox[6] = GetPointIndex(xy6,dims);//Top Top left
			mapBox[7] = GetPointIndex(xy7,dims);//Top Top right
			for(int k = 0; k < 4; k++)
			{
			//	cout <<"mapBox[" << k <<"]: "<< mapBox[k] << endl;		
			}

			vertScalBox[0] = F[mapBox[0]];
			vertScalBox[1] = F[mapBox[1]];
			vertScalBox[2] = F[mapBox[2]];
			vertScalBox[3] = F[mapBox[3]];
			vertScalBox[4] = F[mapBox[4]];
			vertScalBox[5] = F[mapBox[5]];
			vertScalBox[6] = F[mapBox[6]];
			vertScalBox[7] = F[mapBox[7]];
			for(int f = 0; f < 4; f++)
			{
			//	cout << "vertScalBox[" << f <<"]: " << vertScalBox[f] <<endl;	
			}

			//Bottom
		  	percEdgeBox[0] = lerp(vertScalBox[0],vertScalBox[1]);//edge 0    //How high up you should go A -> B 0%->100%
		  	percEdgeBox[1] = lerp(vertScalBox[1],vertScalBox[3]);//edge 1
		  	percEdgeBox[2] = lerp(vertScalBox[2],vertScalBox[3]);//edge 2 
		  	percEdgeBox[3] = lerp(vertScalBox[0], vertScalBox[2]);//edge 3
			//Top
		  	percEdgeBox[4] = lerp(vertScalBox[4], vertScalBox[5]);//edge 4
		  	percEdgeBox[5] = lerp(vertScalBox[5], vertScalBox[7]);//edge 5
		  	percEdgeBox[6] = lerp(vertScalBox[6], vertScalBox[7]);//edge 6
		  	percEdgeBox[7] = lerp(vertScalBox[4], vertScalBox[6]);//edge 7
			//Sides
		  	percEdgeBox[8] = lerp(vertScalBox[0], vertScalBox[4]);//edge 8
		  	percEdgeBox[9] = lerp(vertScalBox[1], vertScalBox[5]);//edge 9
		  	percEdgeBox[10] = lerp(vertScalBox[2], vertScalBox[6]);//edge 10
		  	percEdgeBox[11] = lerp(vertScalBox[3], vertScalBox[7]);//edge 11
			//cout << "percEdgeBox[0]: " << percEdgeBox[0] <<"\npercEdgeBox[1]: " << percEdgeBox[1]
			//<< "\npercEdgeBox[2]: " << percEdgeBox[2] << "\npercEdgeBox[3]: " << percEdgeBox[3] << endl;	
			
			Case = caseChoser(vertScalBox);			
			percLerp(percEdgeBox,lowerLeft,topRight,upperLowerLeft,upperTopRight,edgeValues);
	
		//	cout <<"case: "<<Case <<endl;	
          	float tri[9] = {0,0,0,0,0,0,0,0};
          	bool good = true;
			for(int q = 0; q < 5; q++ )
			{
				for(int t = 0; t < 3; t++)
				{
				    int tempEdge = triCase[Case][3*q+t];
					//cout << "tempEdge: " << tempEdge << endl;
					//cout << 3*q+t << endl;
					cout << "X: " << j<< "Y: " << i << " Z: " << z << endl;
				    if(tempEdge == -1)
				    {
					    good = false;
					    break;
				    }	
				    else if(tempEdge == 0 && good)
				    {
					   tri[3*t+0] = edgeValues[tempEdge];
					   tri[3*t+1] = lowerLeft[1];
					   tri[3*t+2] = lowerLeft[2];
				    }
				    else if(tempEdge == 1 && good)
				    {
					tri[3*t+0] = topRight[0];
					tri[3*t+1] = edgeValues[tempEdge];
					tri[3*t+2] = topRight[2];
				    }
				    else if(tempEdge == 2 && good)
				    {
					tri[3*t+0] = edgeValues[tempEdge];
					tri[3*t+1] = topRight[1];
					tri[3*t+2] = topRight[2];
				    }
				    else if(tempEdge == 3 && good)
				    {
					tri[3*t+0] = lowerLeft[0];
					tri[3*t+1] = edgeValues[tempEdge];
					tri[3*t+2] = lowerLeft[2];
				    }
				    else if(tempEdge == 4 && good)
				    {
					tri[3*t+0] = edgeValues[tempEdge];
					tri[3*t+1] = upperLowerLeft[1];
					tri[3*t+2] = upperLowerLeft[2];
				    }
	 			    else if(tempEdge == 5 && good)
				    {
					tri[3*t+0] = upperTopRight[0];
					tri[3*t+1] = edgeValues[tempEdge];
					tri[3*t+2] = upperTopRight[2];
				    }
				    else if(tempEdge == 6 && good)
				    {
					tri[3*t+0] = edgeValues[tempEdge];
					tri[3*t+1] = upperTopRight[1];
					tri[3*t+2] = upperTopRight[2];
				    }
				    else if(tempEdge == 7 && good)
				    {
					tri[3*t+0] = upperLowerLeft[0];
					tri[3*t+1] = edgeValues[tempEdge];
					tri[3*t+2] = upperLowerLeft[2];
				    }
  				    else if(tempEdge == 8 && good)
				    {
					tri[3*t+0] = lowerLeft[0];
					tri[3*t+1] = lowerLeft[1];
					tri[3*t+2] = edgeValues[tempEdge];
				    }
				    else if(tempEdge == 9 && good)
				    {
					tri[3*t+0] = topRight[0];
					tri[3*t+1] = lowerLeft[1];
					tri[3*t+2] = edgeValues[tempEdge];
				    }
			  	    else if(tempEdge == 10 && good)
				    {
					tri[3*t+0] = lowerLeft[0];
					tri[3*t+1] = topRight[1];
					tri[3*t+2] = edgeValues[tempEdge];
				    }
				    else if(tempEdge == 11 && good)
				    {
					tri[3*t+0] = topRight[0];
					tri[3*t+1] = topRight[1];
					tri[3*t+2] = edgeValues[tempEdge];
				    }

				}//end of tri location loop
			
				tl.AddTriangle(tri[0],tri[1],tri[2],tri[3],tri[4],tri[5],tri[6],tri[7],tri[8]);
			}//end of triaangle for loop
		}//end of y
    }//end of x
}//end of z
    vtkPolyData *pd = tl.MakePolyData();

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
