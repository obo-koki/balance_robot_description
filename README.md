# Balance Robot Description
倒立振子移動ロボットのシミュレーション
![balance_robot](https://user-images.githubusercontent.com/60743930/104920146-b5a27e80-59da-11eb-8a1b-30fabd63d69b.png)

## Usage


### １．ロボットパラメータ
balance_robotdescription/script/robot_param.yaml にロボットのパラメータを保存

### ２．フィードバックゲインを算出するスクリプトを実行
```
$ cd balance_robot_description/script
$ python get_control_gain.py
```
### ３．シミュレータ立ち上げ   
gazebo + rviz
```
roslaunch balance_robot_description sim.launch
```
rvizのみ   
```
roslaunch balance_robot_description robot_display_simple_sim.launch
```
### ４，コントローラ起動
ex)
```
roslaunch balance_robot_description control.launch
```

## Reference

実機用プログラム
https://github.com/obo-koki/balance_robot_control.git

