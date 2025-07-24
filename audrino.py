import cv2
import serial
import time

# Step 1: Connect to Arduino
arduino = serial.Serial('COM3', 9600)  # Change 'COM3' to your port if needed
time.sleep(2)  # Give Arduino time to reset

# Step 2: Load Haar cascades
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade  = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')

# Step 3: Start webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    eyes_detected = False
    for (x, y, w, h) in faces:
        roi_gray = gray[y:y+h, x:x+w]
        eyes = eye_cascade.detectMultiScale(roi_gray)
        if len(eyes) >= 1:
            eyes_detected = True
        break  # Only check one face

    # Step 4: Send command to Arduino
    if eyes_detected:
        arduino.write(b'1')  # Eyes open → LED ON
    else:
        arduino.write(b'0')  # Eyes closed → LED OFF

    # Step 5: Show webcam window
    cv2.imshow('Eye Detection', frame)

    # Exit on pressing 'q'
    if cv2.waitKey(1) == ord('q'):
        break

# Step 6: Clean up
cap.release()
cv2.destroyAllWindows()
arduino.close()
