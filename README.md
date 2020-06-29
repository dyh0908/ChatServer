自己写的一个高并发服务器，正在进行中<br>
编写服务器的过程中主要参考了陈硕的《C++多线程服务器编程》
看完muduo网络库的我在仰望大佬的同时，深深的感觉到了与大佬的差距，怒从零写一个server！！！！希望可以在在了解muduo库主要功能的同时对其进行灵活使用<br>

项目名称 ：ChatServer
-----

可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端源码,基于muduo网络库实现服务端的高并发、高性能，通过nginx进行负载均衡模块设计，通过redis缓存实现跨服务器通信，
实现了高性能、高并发、多服务器的聊天项目。

文件详解：
--------
`/bin`                                                             ：用于生成可执行文件的文件夹，其中包含了生成的client和server。


`/src`  :  包含全部的源文件，分为client和server两大类。


`/thirdparty` :  包含了用到的三方库（这里包含了json.hpp）的文件。


`/include`    :  放置头文件的文件夹，包含了server文件夹和public.hpp —— 因为client客户端的实现简单，所以只在源文件的client中编写了，没有client的头文件。
public.hpp定义了消息的类型，server文件夹下存放的例如chatservice.hpp的头文件，注意server和service的文件不同，server是指整个服务器项目，service是指服务端。
                   
                   
`/build`      :  编译cmake的过程中生成的中间文件，为了提高文件的可读性，查阅方便，将cmake编译后生成的中间文件放
                   到了build里，Makefile同样也在这里面，所以cmake后直接在/build里执行make命令就可以了。
                   
 `/autobuild.sh` : 写了一个简单的脚本以便自动化运行，也可以根据后面的编译方法手动编译。
