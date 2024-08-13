## dynamic project      
    旨在动态管理所有资源，保证所有动态库，资源文件有可控的生命周期       

#### 开发环境及配置     
    1. QtCreator6.0及以上，Windows，linux。 
    2. 内存4GB以上，磁盘250G以上    
    3. qtCreator构建运行配置：      
        a. 配置realese      
        b. Build目录配置为当前项目下的Build目录     
        c. run设置： 
    	   Executable：build目录下 执行项目名.执行文件扩展名
    	   Working directory： 为build设置的build目录
        d. windows的qtcreator编译选项有add library to path(qtcreator 临时编译环境),而linux的qtcreator（ubuntu目前qt5）。
        e. 打包配置：
           对打包后安装目录的lib目录添加到环境变量path中或者library_path中。
           或者将lib目录下*.dll拷贝到执行文件同级目录
           将.config.json拷贝到执行文件目录下
    4. 项目基于C++11，Qt6

#### todo
    1.  需要添加线程池、数据库连接池、状态资源池
