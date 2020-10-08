# Runtime Envirnoment
ubuntu 18.04   
C language  
CMake

# Usage
1.  open a terminal and change the directory to OSMiniProject_Release  
2. create an empty directory  
`
mkdir build 
`
3. change your directory into OSMiniProject_Release/build  
4.  compile the codes.  
`
cmake .. && make 
`
5. run pcbs param generator  (you can generate as much pcbs parameters as you like), then you will get a .txt  file  consist of the pacbs parameters you generated.   
`
./ParamGenerator
`
6. run schedule program  
`
./MiniProject
`

# Author Information
Name: Lixuan Zhang  
E-mail: zhanglixuan0720@stu.xjtu.edu.cn