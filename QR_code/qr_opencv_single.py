"""
Source: Maxim Elkin
"""

import cv2
import numpy as np
# import qrcode
# import qrcode
# qr = qrcode.QRCode(
#     version=1,
#     error_correction=qrcode.constants.ERROR_CORRECT_L,
#     box_size=10,
#     border=4,
# )
# qr.add_data("Turn left is prohibited")
# qr.make(fit=True)
#
# img = qr.make_image(fill_color="black", back_color="white")
#
# img.save("qr_magic3.jpg", "JPEG")

cap = cv2.VideoCapture(0)

while True:
    success, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    detector = cv2.QRCodeDetector()
    data, bbox, clear_qrcode = detector.detectAndDecode(gray)
    print(data)
    if len(data) != 0:
        pts = np.array(bbox[0], np.int32)
        pts = pts.reshape((-1, 1, 2))
        cv2.polylines(img, [pts], True, (0, 255, 0), 5)
        cv2.putText(img, data, (int(bbox[0][0][0]), int(bbox[0][0][1])), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)
        # cv2.rectangle(img,
        #           (int(bbox[0][0][0]), int(bbox[0][0][1])),
        #           (int(bbox[0][2][0]), int(bbox[0][2][1])),
        #           (0, 255, 0),
        #           thickness=2)
    cv2.imshow('Qr Scanner', img)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
