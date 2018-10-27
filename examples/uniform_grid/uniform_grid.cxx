#include <vtkm/cont/DataSet.h>
#include <vtkm/cont/DataSetBuilderUniform.h>
#include <vtkm/cont/DataSetFieldAdd.h>

// this example based on:
//
// "Achieving Portable Performance for Visualization, Using VTK-m"
// pp. 266 - 267
//
// "VTK-m User's Guide"
// p.118


// this function manually creates a 2d data set structured as a uniform grid
vtkm::cont::DataSet manual_grid(void){

  // Step 1
  // instantiate the data set
  vtkm::cont::DataSet ds;
  const int nPoints = 6;
  const int nCells = 2;

  // Step 2
  // build the cell set (and add it to the data set)
  static const vtkm::IdComponent cell_dim = nCells;
  vtkm::cont::CellSetStructured<cell_dim> myCellSet("my_cells");
  myCellSet.SetPointDimensions(vtkm::make_Vec(3,2));
  ds.AddCellSet(myCellSet);

  // Step 3
  // build the coordinate system (and add it to the data set)
  //   note: by default, the first point gets coordinates (0.0, 0.0, 0.0) and the spacing is 1
  //         an optional third agrument changes the first point's coordinates
  //         an optional fourth argument changes the (uniform) spacing
  vtkm::cont::CoordinateSystem myCoordinateSystem("my_coordinates", vtkm::Id3(3,2,1));
  ds.AddCoordinateSystem(myCoordinateSystem);

  // Step 4
  // create a scalar field on the points (and add it to the data set)
  vtkm::Float32 A[nPoints] = {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f};
  vtkm::cont::Field myPointField("my_point_field", vtkm::cont::Field::ASSOC_POINTS, A, nPoints);
  ds.AddField(myPointField);

  // Step 5
  // create a vector field on the cells (and add it to the data set)
  vtkm::Vec<vtkm::Float32,2> B[nCells] = {vtkm::make_Vec(3.0f, -3.0f), vtkm::make_Vec(1.0f, 0.0f)};
  vtkm::cont::Field myCellField("my_cell_field", vtkm::cont::Field::ASSOC_CELL_SET, "my_cells", B, nCells);
  ds.AddField(myCellField);

  // Step 6
  // return the data set!
  return ds;
}


// this function automatically creates a 2d data set structured as a uniform grid
// using the provided convenience classes
vtkm::cont::DataSet auto_grid(void){

  // Step 1
  // instantiate the data set builder
  vtkm::cont::DataSetBuilderUniform builder;

  // Step 2
  // build the data set: this creates the cell set and the coordinate system
  //   note: by default, the first point is at (0.0, 0.0, 0.0) and the spacing is 1
  //         optional second argument to set the first point's coordinates
  //         optional third argument to set custom (uniform) spacing
  vtkm::cont::DataSet ds = builder.Create(vtkm::Id2(3,2));

  // Step 3
  // instantiate the field adder
  vtkm::cont::DataSetFieldAdd field_adder;

  // Step 4
  // add a scalar field to the points
  int nPoints = ds.GetCoordinateSystem().GetData().GetNumberOfValues();  // default is first coordinate system
  vtkm::Float32 A[nPoints] = {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f};
  field_adder.AddPointField(ds, "my_point_field", A, nPoints);

  // Step 5
  // add a vector field to the cells
  int nCells = ds.GetCellSet().GetNumberOfCells();  // default is first cell set
  vtkm::Vec<vtkm::Float32,2> B[nCells] = {vtkm::make_Vec(3.0f, -3.0f), vtkm::make_Vec(1.0f, 0.0f)};
  field_adder.AddCellField(ds, "my_cell_field", B, nCells);

  // Step 6
  // return the data set!
  return ds;
}


int main(int argc, char **argv)
{
  // build the data set manually
  std::cout << std::endl;
  std::cout << "manually building grid data set" << std::endl;
  std::cout << "===============================" << std::endl;
  vtkm::cont::DataSet uniform_grid_manual = manual_grid();
  uniform_grid_manual.PrintSummary(std::cout);

  // build the data set using the convenience classes
  std::cout << std::endl;
  std::cout << "auto building grid data set" << std::endl;
  std::cout << "===============================" << std::endl;
  vtkm::cont::DataSet uniform_grid_auto = auto_grid();
  uniform_grid_auto.PrintSummary(std::cout);

  return 0;
}
