#include <vtkm/cont/ErrorBadValue.h>
#include <vtkm/cont/ArrayHandle.h>

#include <vtkm/worklet/WorkletMapField.h>
#include <vtkm/worklet/DispatcherMapField.h>

#include <vtkm/exec/ExecutionWholeArray.h>

#include "sobel.h"
#include "timing.h"

#define abs(x) ((x)<0 ? -(x) : (x))
#define VTKM_DEVICE_ADAPTER VTKM_DEVICE_ADAPTER_CUDA

class SobelWorklet : public vtkm::worklet::WorkletMapField
{
  public:
    typedef void ControlSignature(FieldIn<vtkm::Int32>,
        FieldOut<vtkm::Int32>, ExecObject);
    typedef void ExecutionSignature(_1, _2, _3);

    VTKM_EXEC_CONT
    vtkm::Int32 operator()(const vtkm::Int32 idx, 
        vtkm::Int32 &out_pixel,
        vtkm::exec::ExecutionWholeArray<vtkm::Int32> &wholeArray) const
    {
      // Move these declarations?
      int Gx[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
      int Gy[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};

      int x_dir = 0;
      int y_dir = 0;

      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

          unsigned int pixel;
          if (idx - (i * COLS) - j >= 0) {
            pixel = wholeArray.Get(idx - (i*COLS) - j);
          }
          else {
            pixel = 0;
          }

          unsigned int r = (pixel >> 16) & 0xff;
          unsigned int g = (pixel >> 8) & 0xff;
          unsigned int b = pixel & 0xff;

          unsigned int luma = r*66 + g*129 + b*25;
          luma = (luma + 128) >> 8;
          luma += 16;

          x_dir += luma * Gx[i][j];
          y_dir += luma * Gy[i][j];

        }
      }

      int temp = abs(x_dir) + abs(y_dir);

      unsigned int clamped;
      if (temp > 128) {
        clamped = 0xffffff;
      }
      else {
        clamped = 0;
      }

      out_pixel = clamped;
    }
};

// sobel filter algorithm
vtkm::cont::ArrayHandle<vtkm::Int32> sobel_filter(
    vtkm::cont::ArrayHandle<vtkm::Int32> inputAH, 
    int threshold) 
{

  // Create output array handle 
  int *output = (int *) malloc(sizeof(int) * ROWS * COLS); 
  vtkm::cont::ArrayHandle<vtkm::Int32> outputAH = 
    vtkm::cont::make_ArrayHandle((vtkm::Int32 *) output, ROWS * COLS);

  // Create index array handle
  int *index = (int *) malloc(sizeof(int) * ROWS * COLS); 
  for (int i = 0; i < ROWS * COLS; i++) index[i] = i;
  vtkm::cont::ArrayHandle<vtkm::Int32> indexAH = 
    vtkm::cont::make_ArrayHandle((vtkm::Int32 *) index, ROWS * COLS);

  vtkm::worklet::DispatcherMapField<SobelWorklet> sobelDispatcher;

  reset_and_start_timer();
  sobelDispatcher.Invoke(indexAH, outputAH, 
      vtkm::exec::ExecutionWholeArray<vtkm::Int32>(inputAH) );
  printf("filter time: %f ms\n", get_elapsed_msec());

  return outputAH;
}

int write_data(vtkm::cont::ArrayHandle<vtkm::Int32> outputAH) 
{
  // Create the portals
  typedef vtkm::cont::ArrayHandle< vtkm::Int32>::PortalControl portalType;
  portalType portal = outputAH.GetPortalControl();

  const char *fname = "frame.ppm";

  FILE *f = fopen(fname, "wb");
  fprintf(f, "P6\n%d %d\n%d\n", COLS, ROWS, 255);
  for(int y = 0; y < ROWS; ++y) {
    for(int x = 0; x < COLS; ++x) {
      unsigned int pixel = portal.Get(y * COLS + x);

      // This assumes byte-order is little-endian.
      fwrite(&pixel, 1, 3, f);
    }
  }

  fclose(f);

  return 0;
}

// this function reads a .ppm file and creates a vtkm  a dataset 
vtkm::cont::ArrayHandle<vtkm::Int32> read_data(const char *input_filename) 
{
  unsigned int *input = (unsigned int *) malloc(sizeof(unsigned int) * ROWS * COLS); 

  // Read the image
  if (!parse_ppm(input_filename, COLS, ROWS, (unsigned char *)input)) {
    fprintf(stderr, "Error: could not load %s\n", input_filename);
    teardown(1);
  }

  int nPoints = ROWS*COLS;

  // need to convert unsigned int to signed int array to avoid errors
  vtkm::cont::ArrayHandle<vtkm::Int32> inputAH = 
    vtkm::cont::make_ArrayHandle((vtkm::Int32 *) input, nPoints);

  return inputAH; 
}

int main(int argc, char **argv)
{

  // get the input file name
  //if (argc < 2) {
  //  printf("usage: sobel input_file\n");
  //  exit(0);
  //}
  //const char *input_filename = argv[1];
  const char *input_filename = "butterflies.ppm";

  // create the VTKm dataset
  vtkm::cont::ArrayHandle<vtkm::Int32> inputAH = read_data(input_filename);

  // Sobel filter
  vtkm::cont::ArrayHandle<vtkm::Int32> sobelAH = sobel_filter(inputAH, 128);

  // write it to the file
  write_data(sobelAH);
  printf("Output written to frame.ppm");

  return 0;
}
