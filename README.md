# Balance Robot Description
倒立振子移動ロボットのシミュレーション
![balance_robot](https://user-images.githubusercontent.com/60743930/104920146-b5a27e80-59da-11eb-8a1b-30fabd63d69b.png)

# Usage

１，balance_robotdescription/script/robot_param.yaml にロボットのパラメータを保存
２，フィードバックゲインを算出するスクリプトを実行
```
$ cd balance_robot_description/script
$ python get_control_gain.py
```
３、ロボットのシミュレーション立ち上げ
```
roslaunch balance_robot_description robot_control_sim.launch
```

# Reference

実機のプログラム
https://github.com/obo-koki/balance_robot_control.git