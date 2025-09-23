# PREFIX MEANINGS
- `n_`    : Number/quantity of something (e.g., n_M1 = number of motor car 1)
- `mass_`    : Mass value in kg (e.g., m_M1 = mass of motor car type 1)
- `r_`    : Resistance due to... value in kN (e.g., r_train = train resistance)
- `f_`    : Force value in kN (e.g., f_motor = motor force)
- `v_`    : Velocity/speed value in km/h (e.g., v_b1 = braking point 1 on certain speed)
- `i_`    : Inertial related value (e.g., i_Cm = inertial coefficient motor)
- `tm_`   : Motor per traction motor/Traction motor (e.g., tm_f = traction force of motor per traction motor)
- `x_`    : Distance related value in m (e.g., s_section = section distance)
- `p_`    : Power related value in kW (e.g., p_wheel = power at wheel)
- `e_`    : Energy consumption related value in kW (e.g., e_regen = energy of regenerative, - e_motor = energy consumption of traction motor)
- `eff_`  : Efficiency related value in % (e.g., eff_gear = efficiency of gearbox)
- `vol_`  : Voltage related value in Volt (e.g., vol_motor = motor voltage)
- `curr_` : RMS Current related value in Ampere (e.g., curr_vvvf = RMS VVVF Current)
- `stat_` : Variables used for static simulation

# GENERIC VARIABLES
- `notch`     : Notch position (-1 to 1)
- `load`      : Load per car (ton)
- `acc`       : Acceleration (km/h/s)
- `dec`       : Deceleration (km/h/s)
- `v`         : Current speed (km/h)
- `startRes`  : Start resistance (N/ton)
- `radius`    : Curve radius (m)
- `slope`     : Track gradient (%)
- `wheel`     : Wheel diameter (mm)
- `adh`       : Adhesion ()

# VARIABLE INFIXES/SUFFIXES
- `_M`                            : Related to motor car
- `_T`                            : Related to trailer car
- `_P`                            : Related to passenger (kg)
- `_p`                            : Related to powering (m/s)
- `_b`                            : Related to braking (m/s)
- `_res`                          : Related to resistance
- `_..i`                          : Related to Inertial
- `_iter`                         : Related to iterative variable
- `..Zero`, `..Five`, `..Ten`, `..TwentyFive` : Related to slope at Zero, Five, Ten, and TwentyFive
- `_disabled`                     : Related to disabled Motor car

# COMPOSITE EXAMPLES
- `mass_totalEmpty`    : Total empty mass of train
- `mass_totalLoad`     : Total loaded mass of train
- `mass_totalInertial` : Total inertial mass of train
- `n_PTc`           : Number of passengers per trailer car
- `n_M1`            : Number of Motor car 1
- `n_ax`            : Number of Axle
- `f_res`           : Resistance force
- `f_brake`         : Braking force
- `r_train`         : Resistance due to train itself at start
- `r_slope`         : Resistance due to slope
- `m_Mi`            : Mass of inertial motor train

# CONSTANTS
- `g`               : Gravitational acceleration (9.8 m/s²)
- `cV`              : Conversion coefficient from m/s to km/h
- `cF`              : Conversion coefficient from kN to kgf

# FORMULAS
- Velocity        : v += acc * dt 
- Acceleration    : a = f_tot / m_totalInertial
- Distance        : x += v * dt