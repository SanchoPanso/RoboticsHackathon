"""
Source: https://betterprogramming.pub/how-to-generate-and-decode-qr-codes-in-python-a933bce56fd0
Docs: https://docs.opencv.org/4.x/de/dc3/classcv_1_1QRCodeDetector.html

In my opinion, it works badly
"""
import cv2
import numpy as np

cap = cv2.VideoCapture(0)
det = cv2.QRCodeDetector()

while True:
    success, img = cap.read()

    retval, decoded_info, points, straight_qrcode = det.detectAndDecodeMulti(img)
    print(decoded_info)

    for i in range(len(decoded_info)):
        pts = np.array(points[i], np.int32)
        pts = pts.reshape((-1, 1, 2))
        cv2.polylines(img, [pts], True, (0, 255, 0), 5)
        cv2.putText(img, decoded_info[i], (int(points[i][0][0]), int(points[i][0][1])),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)

    cv2.imshow('Result', img)
    if cv2.waitKey(1) == 27:  # 'Esc' is pressed
        break
