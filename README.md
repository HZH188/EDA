使用make去构建
运行格式
./EDA_Assess <输入文件.txt> <输出文件.txt>

使用的是改进的穷举算法，先解析文件，再生成所有可能的布局，再计算全部总线长，最后选择最优布局
但是这个算法很慢，如果允许可以使用启发式算法像遗传算法之类的

*添加了剪枝算法和对称情况下不考虑的算法
