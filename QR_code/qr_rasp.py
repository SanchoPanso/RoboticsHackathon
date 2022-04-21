import cv2
import numpy as np

det = cv2.QRCodeDetector()


def qr1(img):
    row = img.copy()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    data, bbox, clear_qrcode = det.detectAndDecode(gray)

    if len(data) != 0:
        pts = np.array(bbox[0], np.int32)
        pts = pts.reshape((-1, 1, 2))
        cv2.polylines(row, [pts], True, (0, 255, 0), 5)
        cv2.putText(row, data, (int(bbox[0][0][0]), int(bbox[0][0][1])), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)

    if data == 'yield':
        return 0, row
    elif data == 'loading':
        return 1, row
    elif data == 'unloading':
        return 2, row
    else:
        return -1, row


def qr2(img):
    row = img.copy()
    retval, decoded_info, points, straight_qrcode = det.detectAndDecodeMulti(img)

    for i in range(len(decoded_info)):
        pts = np.array(points[i], np.int32)
        pts = pts.reshape((-1, 1, 2))
        cv2.polylines(row, [pts], True, (0, 255, 0), 5)
        cv2.putText(row, decoded_info[i], (int(points[i][0][0]), int(points[i][0][1])),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)

    if len(decoded_info) < 1:
        return -1, row
    elif decoded_info[0] == 'yield':
        return 0, row
    elif decoded_info[0] == 'loading':
        return 1, row
    elif decoded_info[0] == 'unloading':
        return 2, row
    else:
        return -1, row

