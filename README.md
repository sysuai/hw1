# 单目标无约束连续优化小组作业

### 更新日志
##### 2018/4/20 11:00
- 撰写了readme
- 创建了目录结构
- 请大家以后更新的时候也简单写一下更新日志

### 小组分工
- 接口标准制定及实验报告：丰光南
- 粒子群算法实现：程钰
- 差分演化算法实现：陈梓阳
- 图形化界面（可视化）：董剑华

### 目录结构
- `document/`作业的doc和我觉得官方有用的文档（不是全部），更多文档请自行上官网
- `codes/`官方的测试函数代码
- `Shifting and Rotation for CEC 2017`/我也不知道这是啥
- `DE/`差分演化算法实现请放在这
- `PSO/`粒子群算法实现请放在这
- `GUI/`可视化实现请放在这

### 题目说明
- 官方提供了30个测试函数，需要寻找他们的最小值
- 官方提供了一个测试函数`cec17_test_func(x)`，这里的“测试代码”的意思是在写程序过程中你生成了一个解x=[x1,x2,……,xn]，然后调用`cec17_test_func(x)`就可以得到这个解对应的值`f(x)`，看下main的例子应该好懂。
- xi的范围在[-100,100],i=1,2,...,d
- 每个测试函数的形式都是Fi(x)=f(g(x-o))+Fi*
- 测试函数Fi(x)的最优值Fi* = Fi(o),按文章意思应该已经给在代码里，且最优解在xi的范围内
- 误差计算就直接用Fi(x)-F*就可以了
- 更多解释看
`document/Definitions of  CEC2017 benchmark suite final version updated.pdf`
第29页Evaluation Criteria

### 程序各个模块接口
- 本次我们采用计算与可视化分离的结构，即分三个代码来写，可视化程序只是输出的两个算法的运行日志
- 程序中需要记录每隔`LOG_DT`秒的M个解
- 程序中请使用`#define`预留以下接口
	- `LOG_DT`运行日志采样间隔
	- `TIME_LIMIT`最大运行时间
	- `FUNC_NUM`要计算的函数编号
	- `DIMENSION`计算维数
- 运行日志按如下格式记录输出到`DE/log.txt`或`PSO/log.txt`
	- 第一行4个数：`FUNC_NUM DIMENSION TIME_LIMIT LOG_DT N`其中N为实际以`LOG_DT`为间隔记录的条数，但不能超过`TIME_LIMIT/LOG_DT+1`
	- 接下来`N*M`行每行`DIMENSION`个数：第ni个M行中的第mi行表示第ni次记录的第mi个解

### ps
- 多多少少会有疏漏，希望大家补充
- 大家上传前如果有缓存文件啥的希望记得gitignore掉
