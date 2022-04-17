"""
Source: https://betterprogramming.pub/how-to-generate-and-decode-qr-codes-in-python-a933bce56fd0
Docs: https://docs.opencv.org/4.x/de/dc3/classcv_1_1QRCodeDetector.html

In my opinion, it works badly
"""
import cv2
cap = cv2.VideoCapture(0)
det = cv2.QRCodeDetector()

while True:
    success, img = cap.read()

    retval, decoded_info, points, straight_qrcode = det.detectAndDecodeMulti(img)
    print(decoded_info)

    cv2.imshow('Result', img)
    if cv2.waitKey(1) == 27:  # 'Esc' is pressed
        cv2.destroyAllWindows()
        break
