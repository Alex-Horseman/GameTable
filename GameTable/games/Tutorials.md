游戏插件教程
------
### 插件文件目录
在game目录下新建文件夹**gamename**，并在**gamename**文件夹中存入**gamename**.txt和所有图片文件。（**gamename**为游戏插件名，可自定义）

### txt代码说明

代码中中括号为可以自定义的变量，包括字符、字符串、数字等。

##### 定义桌面

    TABLE [n] [a] [r] [R] [G] [B]

|变量|类型|描述|
|---|---|---|
|n|int|桌面形状。n=0:圆形;n>=3:n边形|
|a|int|旋转角度（度）|
|r|int|r>0:桌面半径,中心到顶点距离|
|R|int|R=[0:255]桌面颜色R分量|
|G|int|R=[0:255]桌面颜色G分量|
|B|int|R=[0:255]桌面颜色B分量|

#### 定义牌堆

    DECK [S] [x] [y]
    [w] [h] [n] [FI] [BI]
    ...

|变量|类型|描述|
|---|---|---|
|S|char|B:背面向上;F:正面向上|
|x|int|牌堆中心横坐标|
|y|int|牌堆中心纵坐标|
|w|int|w>0,牌宽度|
|h|int|w>0,牌高度|
|n|int|n>=1,堆叠数量|
|FI|string|正面图片文件名|
|BI|string|背面图片文件名|

如指定单张牌时，视为一个只有一张牌的牌堆。

设计非矩形卡牌时，可使用png格式，指定透明区域。

### 范例
    TABLE 4 45 750 0 150 0
    DECK B 0 300
    50 75 30 sheep.jpg back.png
    DECK B 70 300
    50 75 30 wood.jpg back.png
    DECK F 140 300
    50 75 1 wood.jpg back.png

$\color{#FF0000}{0}$
$\color{#FFD500}{1}$
$\color{#00FF80}{3}$
$\color{#00AAFF}{4}$
$\color{#FF00FF}{6}$

$\color{#2A00FF}{5}$
$\color{#55FF00}{2}$
$\color{#FF0000}{7}$