#include <vtkm/cont/DataSet.h>
#include <vtkm/cont/DataSetBuilderExplicit.h>

// this example based on:
//
// "VTK-m User's Guide"
// p.119 - 122


// this function creates a 3d unstructured mesh using the "explicit" scheme
vtkm::cont::DataSet unstructured_explicit(void){

  // Step 1
  // instantiate the convenience class DataSetBuilderExplicitIterative
  vtkm::cont::DataSetBuilderExplicitIterative builder;

  // Step 2
  // add the points (with a coordinate system) to the builder
  builder.AddPoint(-1.0, -1.0, 0.0);  // 0
  builder.AddPoint(1.0, -1.0, 0.0);   // 1
  builder.AddPoint(-1.0, 1.0, 0.0);   // 2
  builder.AddPoint(1.0, 1.0, 0.0);    // 3

  builder.AddPoint(-1.0, -1.0, 3.0);  // 4
  builder.AddPoint(1.0, -1.0, 3.0);   // 5
  builder.AddPoint(-1.0, 1.0, 3.0);   // 6
  builder.AddPoint(1.0, 1.0, 3.0);    // 7

  builder.AddPoint(0.0, 0.0, 5.0);    // 8

  // Step 3
  // explicityly specify each cell
  builder.AddCell(vtkm::CELL_SHAPE_HEXAHEDRON);
  for(int i = 0; i <= 7; i++){
    builder.AddCellPoint(i);
  }

  builder.AddCell(vtkm::CELL_SHAPE_PYRAMID);
  builder.AddCellPoint(4);
  builder.AddCellPoint(5);
  builder.AddCellPoint(6);
  builder.AddCellPoint(7);
  builder.AddCellPoint(8);

  // Step 4
  // return the data set!
  return builder.Create();
}


// this function creates a 3d unstructured mesh using the "connectivity" scheme
vtkm::cont::DataSet unstructured_connectivity(void){

  // Step 1
  // instantiate the convenience class DataSetBuilderExplicit
  vtkm::cont::DataSetBuilderExplicit builder;

  // Step 2
  // define the points (with coordinates)
  std::vector< vtkm::Vec<vtkm::Float32, 3> > pc;
  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(-1.0f, -1.0f, 0.0f));  // 0
  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(1.0f, -1.0f, 0.0f));   // 1
  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(-1.0f, 1.0f, 0.0f));   // 2
  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(1.0f, 1.0f, 0.0f));    // 3

  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(-1.0f, -1.0f, 3.0f));  // 4
  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(1.0f, -1.0f, 3.0f));   // 5
  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(-1.0f, 1.0f, 3.0f));   // 6
  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(1.0f, 1.0f, 3.0f));    // 7

  pc.push_back(vtkm::Vec<vtkm::Float32, 3>(0.0f, 0.0f, 5.0f));    // 8

  // Step 3
  // define the shape types
  std::vector<vtkm::UInt8> shapes;
  shapes.push_back(vtkm::CELL_SHAPE_HEXAHEDRON);
  shapes.push_back(vtkm::CELL_SHAPE_PYRAMID);

  // Step 4
  // give the number of points per cell (this can vary for shapes like POLYGON)
  std::vector<vtkm::IdComponent> np;
  np.push_back(8);
  np.push_back(5);

  // Step 5
  // define the connectivity
  std::vector<vtkm::Id> connectivity;
  for(int i = 0; i <= 7; i++){
    connectivity.push_back(i);
  }  // cell 0

  for(int i = 4; i <= 8; i++){
    connectivity.push_back(i);
  }  // cell 1

  // Step 6
  // return the data set!
  return builder.Create(pc, shapes, np, connectivity);
}


int main(int argc, char **argv)
{
  // build the data set using the "explicit" scheme
  std::cout << std::endl;
  std::cout << "building the unstructured mesh (explicit)" << std::endl;
  std::cout << "=========================================" << std::endl;
  vtkm::cont::DataSet ds1 = unstructured_explicit();
  ds1.PrintSummary(std::cout);
  std::cout << std::endl;
  std::cout << "cells: " << ds1.GetCellSet().GetNumberOfCells() << std::endl;
  std::cout << "faces: " << ds1.GetCellSet().GetNumberOfFaces() << std::endl;
  std::cout << "edges: " << ds1.GetCellSet().GetNumberOfEdges() << std::endl;
  std::cout << "points: " << ds1.GetCellSet().GetNumberOfPoints() << std::endl;

  // build the data set using the "connectivity" scheme
  std::cout << std::endl;
  std::cout << "building the unstructured mesh (connectivity)" << std::endl;
  std::cout << "=============================================" << std::endl;
  vtkm::cont::DataSet ds2 = unstructured_connectivity();
  ds2.PrintSummary(std::cout);
  std::cout << std::endl;
  std::cout << "cells: " << ds2.GetCellSet().GetNumberOfCells() << std::endl;
  std::cout << "faces: " << ds2.GetCellSet().GetNumberOfFaces() << std::endl;
  std::cout << "edges: " << ds2.GetCellSet().GetNumberOfEdges() << std::endl;
  std::cout << "points: " << ds2.GetCellSet().GetNumberOfPoints() << std::endl;

  return 0;
}
