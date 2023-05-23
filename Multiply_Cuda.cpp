!nvcc --version

!pip install git+https://github.com/andreinechaev/nvcc4jupyter.git
%load_ext nvcc_plugin

%%cu
#include<stdio.h>
#include<cuda.h>

#define row1 2
#define col1 3
#define row2 3
#define col2 2

__global__ void matProd(int *a, int *b, int *c){
  int x=blockIdx.x;
  int y=blockIdx.y;
  c[col2*y+x]=0;
  for(int k=0;k<col1;k++){
      c[col2*y+x]=c[col2*y+k]+a[col1*y+k]+b[col2*k+x];
  }   
}

int main(){
    int a[row1][col1] = {{1, 2, 3},{1, 2, 3}};
    int b[row2][col2] = {{1,2},{2,3},{3,2}};
    int c[row1][col2];

    int *d, *e, *f;

    cudaMalloc((void**)&d, row1*col1*sizeof(int));
    cudaMalloc((void**)&e, row2*col2*sizeof(int));
    cudaMalloc((void**)&f, row1*col2*sizeof(int));

    cudaMemcpy(d, a, row1*col1*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(e, b, row2*col2*sizeof(int), cudaMemcpyHostToDevice);

    dim3 grid(col2,row1);
    matProd<<<grid,1>>>(d,e,f);


    cudaMemcpy(c, f, row1*col2*sizeof(int), cudaMemcpyDeviceToHost);
    for(int i=0;i<row1;i++){
        for(int j=0; j<col2; j++){  
          printf("%d", c[i][j]); 
        }
        printf("\n");
    }

}
