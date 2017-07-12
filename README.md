# CodeLink
A Simulink Like IDE for C++ based on nana gui. 
By it developers are allowed to write code as well as draw blocks in just one environment.
Basic blocks should be developed by code, programmable and user defined. 
Developers can develop, test, and even sumulate their codes or blocks in CodeLink.
CodeLink should be able to generate executable file or script, which can be run on target machine. 
Tip: Source code is in a CodeBlocks project. 

To take advantage of QT chart and QT 3D, future work will depended on QT. All functions in this project will be rewritten in its QT version.

It is a big idea, I need more people to help me to realize it.

![github](https://github.com/Tumiz/CodeLink/raw/master/sample.PNG)
![github](https://github.com/Tumiz/CodeLink/raw/master/sample.gif)

6.16.2017
This project is blocked by losing interest and lacking of related skills for a long time. I spent most of my time on my work like a Qt engineer in Huawei and have few spare time to continue this project. Now I find a easy job in my hometown and I will restart the project again.

Previously, I always try to make a tool like Simulink. Though a prototype was carried out based on Nana GUI, I found it very hard to carry on because of its complex GUI technologies. I have no idea how to handle so many blocks until I find this tool's basic function should be testing C/C++ functions. There is not such a thing in the world that can test C/C++ functions visually, and it is not difficult to implement. Just one block is OK at first, not a lot of blocks that I cant handle. 

Another problem is that I have no knowledge about communication between processes. Zmq is taken in consideration, but it is still complex. QProcess provide a easier way to master communication between just two processes. Both giving input and getting output can be implemented within four or five code lines.

CodeLink needs two processes basically. One in the front as GUI process, call compiler to compile C/C++ code, input and output. Another at the background as an operation process, execute binary file, calculate and feedback result. I compared serval compliers, GCC is old, msvc lacks documents, so I am willing to choose Clang. If you have better idea, pls contect me via hh11698@163.com. Thank you for your attention.

7.12.2017
I uploaded a related project https://github.com/Tumiz/CppTestBench. It is a prototype of CodeLink with a simple UI.
