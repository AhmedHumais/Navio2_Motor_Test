# Navio2_Motor_Test

## _How to use_

```
git clone https://github.com/AhmedHumais/Navio2_Motor_Test.git
cd Navio2_Motor_Test
mkdir build
cd build
cmake ..
make
./motor_run
```

## _How to send commands to motors_

```<mot_num> <command>```

- Note: mot_num is index of motor pin starting from 0. while command is pulse width in microseconds as accepted by ESCs, for example: 1500
