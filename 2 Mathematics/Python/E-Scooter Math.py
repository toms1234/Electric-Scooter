from math import sin, atan

m_pi = 3.14159265358979323846264338327950288    # could've also used pi from math library
kmh_mph_ratio = 0.6213712   # used to convert km/h to mph
gravity = 9.81      # m/s^2

motor_rpm = 4000    # rpm at 6S LiPo, can go up to 14S with our ESC
motor_watt = 1125   # watts at 6S LiPo

wheel_dia = 0.2     # meter
scooter_mass = 10   # kg

try:
    print("\n------------- Electric Scooter -------------\n")

    drive_teeth = float(input("  Amount of teeth on the drive sprocket: "))
    driven_teeth = float(input("  Amount of teeth on the driven sprocket: "))

    gear_ratio = driven_teeth/drive_teeth
    print("\n  Gear ratio = %.2f" % gear_ratio)
    print("  Motor RPM = " + str(motor_rpm))

    wheel_rpm = motor_rpm/gear_ratio
    print("  Wheel RPM = %.2f" % wheel_rpm)

    speed_ms = (m_pi * wheel_dia * wheel_rpm) / 60
    print("\n  Theoretical speed (excl. drag) = %.2f m/s" % speed_ms)
    speed_kmh = speed_ms * 3.6
    print("  Theoretical speed (excl. drag) = %.2f km/h" % speed_kmh + " = %.2f mph" % (speed_kmh * kmh_mph_ratio))

    motor_torque = motor_watt / ((2 * m_pi * motor_rpm) / 60)
    print("\n  Motor torque (excl. losses) = %.2f Nm" % motor_torque)
    wheel_torque = motor_torque * gear_ratio
    print("  Wheel torque (excl. losses) = %.2f Nm" % wheel_torque)

    print("\n---------------- Situation ----------------\n")

    hill_percentage = input("  Driving up a hill with percentage (%): ")

    desired_speed = input("  At a constant speed of (km/h): ")
    person_mass = input("  Person's weight (kg): ")
    total_mass = scooter_mass + float(person_mass)

    necessary_watt = total_mass * gravity * sin(atan(float(hill_percentage) / 100)) * (float(desired_speed) / 3.6)
    print("\n  Necessary wattage to go up that hill = %.2f W" % necessary_watt)
    necessary_torque = total_mass * gravity * sin(atan(float(hill_percentage) / 100)) * (wheel_dia / 2)
    print("  Necessary torque to go up that hill = %.2f Nm" % necessary_torque)

    if wheel_torque > necessary_torque:
        print("\n  We've got enough torque to go up that hill!\n")
    else:
        print("\n Not enough torque to go up that hill...")
        print("  Possible solutions:")
        print("\t> Adjust the gear ratio")
        print("\t> Make the wheels diameter smaller")
        print("\t> Buy a bigger, much stronger, motor and battery")
        print("\t> Never try getting up that hill again")
        print("\t> Go to a planet with less gravity")
        print("\t> Lose weight")

except ValueError:
        spacing = "  "
        new_line = "\n"
        error = " ERROR "
        string = "Learn to type a number."
        print(new_line + spacing + (int(((len(string) - len(error))/2))*"-") + error + (int(((len(string) - len(error))/2))*"-"))
        print(new_line + spacing + string)
        print(new_line + spacing + len(string) * "-")

