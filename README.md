# Balance Robot Description
倒立振子移動ロボットのシミュレーション
![balance_robot](https://user-images.githubusercontent.com/60743930/104920146-b5a27e80-59da-11eb-8a1b-30fabd63d69b.png)

## Installation
diff_drive_controller_effort

https://github.com/obo-koki/diff_drive_controller_effort

bobble_controllers

https://github.com/obo-koki/bobble_controllers
※branchをbalance_robotに変更すること

## Usage
### １．ロボットパラメータ
balance_robotdescription/script/robot_param.yaml にロボットのパラメータを保存

### ２．フィードバックゲインを算出するスクリプトを実行
```
$ cd balance_robot_description/script
$ python get_control_gain.py
```
### ３．シミュレータ立ち上げ   
#### 自作プログラム 
gazebo + rviz
```
roslaunch balance_robot_description sim_simple.launch
```
rvizのみ   
```
roslaunch balance_robot_description robot_display_simple_sim.launch
```
#### 参考プログラム(bobble)
gazebo
```
roslaunch balance_robot_description bobble_sim.launch
```

### ４. コントローラ起動
#### 自作プログラム
```
roslaunch balance_robot_description control.launch
```
#### 参考プログラム(bobble)
```
roslaunch balance_robot_description bobble_control.launch
```

### ５. ロボットの傾きと速度の測定
#### シミュレーションのスタートと記録 (gazeboとcontrollerは立ち上げておく)
```
roscd bobble_controllers/analysis
rosrun bobble_controllers BalanceRobotStateHold
```
#### グラフ化
```
python make_plots.py --run BalanceData.bag
```
![Screenshot from 2021-05-30 22-37-58](https://user-images.githubusercontent.com/60743930/120106413-cf797c80-c197-11eb-92cf-b1c5c023a00e.png)
## Reference

実機用プログラム

https://github.com/obo-koki/balance_robot_control.git

参考プログラム(bobble_controllers)

https://github.com/super-owesome/bobble_controllers