# Runtime Envirnoment
ubuntu 18.04   
C language  
CMake

# Usage
1. open a terminal and clone the files from github.  
`
git clone git@github.com:zhanglixuan0720/OSMiniPrject.git
`  
2. change the directory to OSMiniProject_Release and create an empty directory    
`
cd OSMiniProject/OSMiniProject_Release && mkdir build 
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
7.  if you want to print the output into file and check them carefully, you can run  
`
./MiniProject | tee ../OutputFile.txt
`  
and you will get a output file in the directory: OSMiniProject_Release     
## Note
 if you run step 7, you are required to choose the algorithm number without prompt. I recommend you run step 6 before trying to run step 7 becease both of them require the same input and the step 6 will give you some prompt messages.
# Author Information
Name: Lixuan Zhang  
E-mail: zhanglixuan0720@stu.xjtu.edu.cn
