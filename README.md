# 前言
这里是西安交通大学RoboMaster笃行机器人队校内赛第五组的电控代码仓库

# 开发过程中的碎碎念
好

generate code之后会报错，把报错那行注释掉就行

LED初始化会亮白灯，快速模式是红灯，慢速是绿灯，关控是白灯

要改灵敏度去shift_task改coefficient

我这个pwm应该写的有问题，打开pwm后会根据初始化给的pulse持续转动而不是固定在一个位置，而且不用给占空比。。。。pulse在200和400刚好方向不同且速度差不多所以我这么取的值

直流电机我没写调速，直接最快，不方便的话可以换成pwm

另外我们拨轮有问题，和6组一样，正值能到5000，负值只能往下拨一点点，最大-1024，再往下拨就变正的660了，需要微操（