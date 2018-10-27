#include <vtkm/io/reader/VTKDataSetReader.h>
#include <vtkm/io/writer/VTKDataSetWriter.h>


// based on the example provided at:
//
//    https://gitlab.kitware.com/kmorel/vtkm-exercises


// read in a .vtk file, goof around with the coordinate system,
// and write it back out as a .vtk file
void read_and_write(const char *in_filename, const char *out_filename)
{

  // Step 1
  // Create a vtkm::io::reader::VTKDataSetReader object. The constructor for
  // VTKDataSetReader takes the filename.
  std::cout << std::endl;
  std::cout << "Loading file: " << in_filename << std::endl;
  vtkm::io::reader::VTKDataSetReader reader(in_filename);

  // Step 2
  // Use the reader object to load the data from the file. This is done by
  // calling the ReadDataSet method. The resulting data is returned in a
  // vtkm::cont::DataSet object.
  vtkm::cont::DataSet inData = reader.ReadDataSet();

  // Step 3
  // print a summary of the data set
  std::cout << std::endl;
  inData.PrintSummary(std::cout);

  // Step 4
  // get the coordinate system
  vtkm::cont::CoordinateSystem coordinates = inData.GetCoordinateSystem();

  // Step 5
  // the data for the coordinate system is in a dynamic array handle, we
  // need to turn it into an array handle to mess around with it
  vtkm::cont::DynamicArrayHandleCoordinateSystem dynamic_handle = coordinates.GetData();
  std::vector< vtkm::Vec<vtkm::Float32, 3> > cs_buffer(dynamic_handle.GetNumberOfValues());
  vtkm::cont::ArrayHandle< vtkm::Vec<vtkm::Float32, 3> > concrete_handle = vtkm::cont::make_ArrayHandle(cs_buffer);
  dynamic_handle.CopyTo(concrete_handle);

  // Step 6
  // modify the coordinate system to multiply each coordinate point by 1/10
  typedef vtkm::cont::ArrayHandle< vtkm::Vec<vtkm::Float32, 3> >::PortalControl portalType;
  portalType portal = concrete_handle.GetPortalControl();
  for(vtkm::Id idx = 0; idx < portal.GetNumberOfValues(); idx++){
    vtkm::Vec<vtkm::Float32, 3> v = portal.Get(idx);
    vtkm::Vec<vtkm::Float32, 3> new_v(v[0] / 10.0, v[1] / 10.0, v[2] / 10.0);
    portal.Set(idx, new_v);
  }

  // Step 7
  // look at the data set again
  std::cout << std::endl;
  inData.PrintSummary(std::cout);

  // Step 8
  // write the dataset to a .vtk file
  std::cout << std::endl;
  std::cout << "Writing file: " << out_filename << std::endl;
  vtkm::io::writer::VTKDataSetWriter writer(out_filename);
  writer.WriteDataSet(inData);
}


int main(int argc, char **argv)
{

  if (argc < 3)
  {
    std::cerr << "USAGE: " << argv[0] << " <in_filename>.vtk <out_filename>.vtk" << std::endl;
    return 1;
  }
  const char *infilename = argv[1];
  const char *outfilename = argv[2];

  // the referenced example says this is good!
  try
  {
    read_and_write(infilename, outfilename);
  }
  catch (vtkm::cont::Error &error)
  {
    std::cerr << "Encountered VTK-m error:" << std::endl;
    std::cerr << error.GetMessage() << std::endl;
  }

  return 0;
}
