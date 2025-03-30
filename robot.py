from flask import Flask, request
import RPi.GPIO as GPIO
import time

# Setup GPIO mode
GPIO.setmode(GPIO.BCM)

# Define motor pins (PWM for omni wheels)
omni_wheel_pins = {
    "front_left": 17,
    "front_right": 18,
    "back_left": 27,
    "back_right": 22
}

# Define linear actuator pin
linear_actuator_pin = 23

# Define servo pins
servo_pins = {"servo_1": 24, "servo_2": 25}

# Setup motor and actuator pins
for pin in omni_wheel_pins.values():
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

GPIO.setup(linear_actuator_pin, GPIO.OUT)
GPIO.output(linear_actuator_pin, GPIO.LOW)

# Setup servos
servo_pwm = {}
for name, pin in servo_pins.items():
    GPIO.setup(pin, GPIO.OUT)
    servo_pwm[name] = GPIO.PWM(pin, 50)
    servo_pwm[name].start(7.5)

app = Flask(__name__)

def set_motor_speeds(fl, fr, bl, br):
    GPIO.output(omni_wheel_pins["front_left"], fl)
    GPIO.output(omni_wheel_pins["front_right"], fr)
    GPIO.output(omni_wheel_pins["back_left"], bl)
    GPIO.output(omni_wheel_pins["back_right"], br)

@app.route('/drive', methods=['POST'])
def drive():
    command = request.json.get("command")
    if not command:
        return {"status": "error", "message": "No command received"}, 400
    
    handle_command(command)
    return {"status": "success", "message": f"Command '{command}' executed"}

def handle_command(command):
    if command == "forward":
        set_motor_speeds(1, 1, 1, 1)
    elif command == "backward":
        set_motor_speeds(0, 0, 0, 0)
    elif command == "left":
        set_motor_speeds(0, 1, 1, 0)
    elif command == "right":
        set_motor_speeds(1, 0, 0, 1)
    elif command == "stop":
        set_motor_speeds(0, 0, 0, 0)
    elif command == "extend_actuator":
        GPIO.output(linear_actuator_pin, 1)
    elif command == "retract_actuator":
        GPIO.output(linear_actuator_pin, 0)
    elif command.startswith("servo_1"):
        angle = int(command.split("_")[-1])
        set_servo_angle("servo_1", angle)
    elif command.startswith("servo_2"):
        angle = int(command.split("_")[-1])
        set_servo_angle("servo_2", angle)
    else:
        print("Unknown command")

def set_servo_angle(servo, angle):
    duty_cycle = (angle / 18) + 2.5
    servo_pwm[servo].ChangeDutyCycle(duty_cycle)
    time.sleep(0.5)
    servo_pwm[servo].ChangeDutyCycle(0)

if __name__ == "__main__":
    try:
        app.run(host='0.0.0.0', port=5000)
    finally:
        GPIO.cleanup()
