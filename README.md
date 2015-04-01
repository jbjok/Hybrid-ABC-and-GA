# Hybrid-ABC-and-GA
Regression Test-Suite Minimization using an Hybrid Technique based on ABC and Genetic Algorithm 

Regression testing is a testing activity that is performed to provide confidence that changes do not harm
the existing behavior of the software. Test suites tend to grow in size as software evolve, often making it too costly
to execute entire test suites. Thus it becomes a necessity to choose the minimum set of test cases with the ability to
cover all the faults in minimum time. A new hybrid approach based on artificial bee colony algorithm and genetic
algorithm was proposed to reduce the test suite. This paper implement the proposed approach and perform empirical
study to evaluate the correctness and efficiency.


1、开发平台为VS2013，C++实现，使用了boost库，如果要编译运行，请下载boost库并按官方说明配置VS项目。

2、测试程序默认读取D盘的siemens目录下的数据文件，如果调试运行，请注意main函数里面的参数。