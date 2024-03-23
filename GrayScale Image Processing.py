import math
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import os.path

### 함수부
#*********************

### 공통 함수부
#*********************
def malloc2D(h, w, initValue=0):
    memory = [ [initValue for _ in range(w)] for _ in range(h)]
    return memory

def openImage():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    global mainMenu, fileMenu

    fullname = askopenfilename(parent=window, filetypes=(('RAW파일', '*.raw'), ('모든 파일', '*.*')))

    # 취소
    if fullname == '':
        return

    #중요! 입력 이미지 크기를 결정
    fsize = os.path.getsize(fullname) # 파일 크기(Byte)
    inH = inW = int(math.sqrt(fsize))

    #메모리 할당
    inImage = malloc2D(inH, inW)

    # 파일 --> 메모리
    rfp = open(fullname, 'rb')
    for i in range(inH):
        for j in range(inW):
            inImage[i][j] = ord(rfp.read(1))

    rfp.close()
    equalImage()

    # 메뉴 활성화
    fileMenu.entryconfig('저장', state='normal')
    mainMenu.entryconfig('화소 점 처리', state='normal')
    mainMenu.entryconfig('기하학 처리', state='normal')
    mainMenu.entryconfig('히스토그램 처리', state='normal')
    mainMenu.entryconfig('영역 처리', state='normal')

def saveImage():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # if outImage == None or len(outImage) == 0: # 영상 처리를 한 적 X
    #     return

    wfp = asksaveasfile(parent=window, mode='wb', defaultextension='*.raw', filetypes=(('RAW파일', '*.raw'), ('모든 파일', '*.*')))

    # 취소
    if wfp is None:
        return

    import struct
    for i in range(outH):
        for j in range(outW):
            wfp.write(struct.pack('B', outImage[i][j]))

    wfp.close()
    messagebox.showinfo('성공', wfp.name + '\n이 위치에 파일이 저장되었습니다.')

def onExit():
    if messagebox.askokcancel('Quit', '프로그램을 종료하시겠습니까?'):
        window.destroy()

def displayImage():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    global histogramMenu

    ## 기존에 이미지를 오픈한 적이 있으면, 캔버스 뜯어내기
    if canvas != None:
        canvas.destroy()

    ## 벽, 캔버스, 종이 설정
    window.geometry(str(outH) + 'x' + str(outW)) # '512x512'
    canvas = Canvas(window, height=outH, width=outW, bg='yellow')  # 칠판
    paper = PhotoImage(height=outH, width=outW)
    canvas.create_image(outH // 2, outW // 2, image=paper, state='normal')

    ## 메모리 --> 화면
    # for i in range(outH):
    #     for j in range(outW):
    #         r = g = b = outImage[i][j]
    #         paper.put('#%02x%02x%02x' % (r, g, b), (j, i))
    # 더블 버퍼링과 비슷한 기법 (모두 다 메모리 상에 생성한 후에, 한 방에 출력)
    rgbString = '' # 전체에 대한 16진수 문자열

    for i in range(outH):
        oneString = '' # 한 줄에 대한 16진수 문자열

        for j in range(outW):
            r = g = b = outImage[i][j]
            oneString += '#%02x%02x%02x ' % (r, g, b)

        rgbString += '{' + oneString + '} '

    paper.put(rgbString)
    canvas.pack()

    # 다른 메뉴 클릭 시 히스토그램 비교 불가
    histogramMenu.entryconfig('히스토그램 비교', state='disabled')

def makeDataImage():
    global inImage, dataImage, inH, inW

    dataImage = malloc2D(inH, inW)

    for i in range(inH):
        for j in range(inW):
            dataImage[i][j] = 0

    num, size = 1, inH // 4

    for i in range(inH // 2 - size, inH // 2, 1):
        for j in range(inW // 2 - num, inW // 2 + num, 1):
            dataImage[i][j] = 255

        num += 1

    num -= 1

    for i in range(inH // 2, inH // 2 + size, 1):
        for j in range(inW // 2 - num, inW // 2 + num, 1):
            dataImage[i][j] = 255

        num -= 1

def makeHistGraph():
    global inHisto, outHisto
    import matplotlib.pyplot as plt

    plt.figure(figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.hist(inHisto, bins=255, color='skyblue')
    plt.xlabel('input')

    plt.subplot(1, 2, 2)
    plt.hist(outHisto, bins=255, label='output', color='pink')
    plt.xlabel('output')

    plt.xlim([0, 255])
    plt.show(block=False)
    plt.pause(5)
    plt.close()

#*********************
### 영상 처리 함수부
#*********************
def equalImage(): # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            outImage[i][j] = inImage[i][j]
    #############################

    displayImage()

def addImage(): # 밝게/어둡게
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    value = askinteger('정수 입력', '-255 ~ 255 입력', minvalue=-255, maxvalue=255)

    # 취소
    if value is None:
        return

    for i in range(inH):
        for j in range(inW):
            px = inImage[i][j] + value

            if px < 0:
                px = 0
            elif 255 < px:
                px = 255

            outImage[i][j] = px
    #############################

    displayImage()

def mulImage(): # 더 밝게/어둡게
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    value = askfloat('소수 입력', '0 이상 입력', minvalue=0)

    # 취소
    if value is None:
        return

    for i in range(inH):
        for j in range(inW):
            px = int(inImage[i][j] * value)

            if px < 0:
                px = 0
            elif 255 < px:
                px = 255

            outImage[i][j] = px
    #############################

    displayImage()

def andImage(): # AND
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    makeDataImage()

    for i in range(inH):
        for j in range(inW):
            px = inImage[i][j] & dataImage[i][j]

            if px < 0:
                px = 0
            elif 255 < px:
                px = 255

            outImage[i][j] = px

    #############################

    displayImage()

def orImage(): # OR
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    makeDataImage()

    for i in range(inH):
        for j in range(inW):
            px = inImage[i][j] | dataImage[i][j]

            if px < 0:
                px = 0
            elif 255 < px:
                px = 255

            outImage[i][j] = px

    #############################

    displayImage()

def xorImage(): # XOR
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    makeDataImage()

    for i in range(inH):
        for j in range(inW):
            px = inImage[i][j] ^ dataImage[i][j]

            if px < 0:
                px = 0
            elif 255 < px:
                px = 255

            outImage[i][j] = px
    #############################

    displayImage()

def notImage(): # NOT
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            outImage[i][j] = 255 - inImage[i][j]
    #############################

    displayImage()

def gammaImage(): # 감마
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    gamma = askfloat('소수 입력', '감마 값')

    # 취소
    if gamma is None:
        return

    for i in range(inH):
        for j in range(inW):
            x = inImage[i][j]
            outImage[i][j] = int(255.0 * math.pow(x / 255.0, gamma))
    #############################

    displayImage()

def parabolaCapImage(): # 파라볼라(CAP)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            x = inImage[i][j]
            outImage[i][j] = int(-255.0 * math.pow(x / 127.0 - 1.0, 2) + 255.0)
    #############################

    displayImage()

def parabolaCupImage(): # 파라볼라(CUP)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            x = inImage[i][j]
            outImage[i][j] = int(255.0 * pow(x / 127.0 - 1.0, 2))
    #############################

    displayImage()

def posterizing(): # 포스터라이징
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    value = askinteger('정수 입력', '단계 수', minvalue=3, maxvalue=255)

    # 취소
    if value is None:
        return

    for i in range(inH):
        for j in range(inW):
            for k in range(1, value, 1):
                if k is (value - 1):
                    outImage[i][j] = 255
                elif inImage[i][j] <= 255 // (value - 1) * k:
                    if k == 1:
                        outImage[i][j] = 0
                    else:
                        outImage[i][j] = 255 // (value - 2) * (k - 1)

                    break
    #############################

    displayImage()

def stressImage(): # 강조
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    value1 = askinteger('정수 입력', '시작 구간 (0 ~ 255)', minvalue=0, maxvalue=255)
    # 취소1
    if value1 is None:
        return

    value2 = askinteger('정수 입력', '마지막 구간 (0 ~ 255)', minvalue=0, maxvalue=255)
    # 취소2
    if value2 is None:
        return

    for i in range(inH):
        for j in range(inW):
            if value1 <= inImage[i][j] and inImage[i][j] <= value2:
                outImage[i][j] = 255
            else:
                outImage[i][j] = inImage[i][j]
    #############################

    displayImage()

def bwImage(): # 흑백
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            if inImage[i][j] < 128:
                outImage[i][j] = 0
            else:
                outImage[i][j] = 255
    #############################

    displayImage()

def bwAvgImage(): # 흑백(평균값)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    avg = 0

    for i in range(inH):
        for j in range(inW):
            avg += inImage[i][j]

    avg /= inH * inW

    for i in range(inH):
        for j in range(inW):
            if inImage[i][j] < avg:
                outImage[i][j] = 0
            else:
                outImage[i][j] = 255
    #############################

    displayImage()

def bwMedImage(): # 흑백(중앙값)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    arr = []

    for i in range(inH):
        for j in range(inW):
            arr.append(inImage[i][j])

    arr.sort()
    med = arr[inH * inW // 2]

    for i in range(inH):
        for j in range(inW):
            if inImage[i][j] < med:
                outImage[i][j] = 0
            else:
                outImage[i][j] = 255
    #############################

    displayImage()

def zoomOut(): # 축소(포워딩)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '축소 n배')

    # 취소
    if scale is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH // scale
    outW = inW // scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            outImage[i // scale][j // scale] = inImage[i][j]
    #############################

    displayImage()

def zoomOutAvg(): # 축소(평균값)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '축소 n배')

    # 취소
    if scale is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH // scale
    outW = inW // scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(0, inH, scale):
        for j in range(0, inW, scale):
            avg = 0

            for n in range(0, scale, 1):
                for m in range(0, scale, 1):
                    avg += inImage[i + n][j + m]

            outImage[i // scale][j // scale] = avg // (scale * scale)
    #############################

    displayImage()

def zoomOutMed(): # 축소(중앙값)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '축소 n배')

    # 취소
    if scale is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH // scale
    outW = inW // scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(0, inH, scale):
        for j in range(0, inW, scale):
            arr = []

            for n in range(0, scale, 1):
                for m in range(0, scale, 1):
                    arr.append(inImage[i + n][j + m])

            arr.sort()

            outImage[i // scale][j // scale] = arr[scale * scale // 2]
    #############################

    displayImage()

def zoomIn1(): # 확대(포워딩)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '확대 n배')

    # 취소
    if scale is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH * scale
    outW = inW * scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            outImage[i * scale][j * scale] = inImage[i][j]
    #############################

    displayImage()

def zoomIn2(): # 확대(백워딩)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '확대 n배')

    # 취소
    if scale is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH * scale
    outW = inW * scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = inImage[i // scale][j // scale]
    #############################

    displayImage()

def zoomInBilinear(): # 확대(양선형 보간)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '확대 n배')

    # 취소
    if scale is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH * scale
    outW = inW * scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 빈 자리 채우기
    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = inImage[i // scale][j // scale]

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(outH):
        for j in range(outW):
            rH = i / scale
            rW = j / scale

            iH = int(math.floor(rH))
            iW = int(math.floor(rW))

            sH = rH - iH
            sW = rW - iW

            if iH < 0 or inH - 1 <= iH or iW < 0 or inW - 1 <= iW:
                outImage[i][j] = 255
            else:
                C1 = float(inImage[iH][iW])
                C2 = float(inImage[iH][iW + 1])
                C3 = float(inImage[iH + 1][iW + 1])
                C4 = float(inImage[iH + 1][iW])

                outImage[i][j] = int(C1 * (1 - sH) * (1 - sW) + C2 * sW
                                     * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH)
    #############################

    displayImage()

def rotate(): # 회전
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = 0

    degree = askinteger('정수 입력', '회전 각도', minvalue=0, maxvalue=360)

    # 취소
    if degree is None:
        return

    radian = -degree * 3.141592 / 180.0

    for i in range(inH):
        for j in range(inW):
            xs = i
            ys = j

            xd = int(math.cos(radian) * xs - math.sin(radian) * ys)
            yd = int(math.sin(radian) * xs + math.cos(radian) * ys)

            if (0 <= xd and xd < outH) and (0 <= yd and yd < outW):
                outImage[xd][yd] = inImage[xs][ys]
    #############################

    displayImage()

def rotate2(): # 회전(중앙+백워딩)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = 0

    degree = askinteger('정수 입력', '회전 각도', minvalue=0, maxvalue=360)

    # 취소
    if degree is None:
        return

    radian = -degree * 3.141592 / 180.0

    cx = inH // 2
    cy = inW // 2

    for i in range(outH):
        for j in range(outW):
            xd = i
            yd = j

            xs = int(math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy))
            ys = int(-math.sin(radian) * (xd - cx) + math.cos(radian) * (yd - cy))

            xs += cx
            ys += cy

            if (0 <= xs and xs < outH) and (0 <= ys and ys < outW):
                outImage[xd][yd] = inImage[xs][ys]
    #############################

    displayImage()

def rotateZoomIn(): # 회전(확대)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '확대 n배')
    # 취소1
    if scale is None:
        return

    degree = askinteger('정수 입력', '회전 각도', minvalue=0, maxvalue=360)
    # 취소2
    if degree is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = tmpH = inH * scale
    outW = tmpW = inW * scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpImage = malloc2D(tmpH, tmpW)

    #### 진짜 영상 처리 알고리즘 ####
    radian = -degree * 3.141592 / 180.0

    # 확대
    for i in range(outH):
        for j in range(outW):
            tmpImage[i][j] = inImage[i // scale][j // scale]

    # 회전
    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = 0

    cx = tmpH // 2
    cy = tmpW // 2

    for i in range(outH):
        for j in range(outW):
            xd = i
            yd = j

            xs = int(math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy))
            ys = int(-math.sin(radian) * (xd - cx) + math.cos(radian) * (yd - cy))

            xs += cx
            ys += cy

            if (0 <= xs and xs < outH) and (0 <= ys and ys < outW):
                outImage[xd][yd] = tmpImage[xs][ys]
    #############################

    displayImage()

def rotateZoomInBilinear(): # 회전(확대+양선형)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    scale = askinteger('정수 입력', '확대 n배')
    # 취소1
    if scale is None:
        return

    degree = askinteger('정수 입력', '회전 각도', minvalue=0, maxvalue=360)
    # 취소2
    if degree is None:
        return

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = tmpH = inH * scale
    outW = tmpW = inW * scale

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpImage = malloc2D(tmpH, tmpW)

    #### 진짜 영상 처리 알고리즘 ####
    radian = -degree * 3.141592 / 180.0

    # 빈 자리 채우기
    for i in range(outH):
        for j in range(outW):
            tmpImage[i][j] = inImage[i // scale][j // scale]

    # 확대(양선형 보간)
    for i in range(outH):
        for j in range(outW):
            rH = i / scale
            rW = j / scale

            iH = int(math.floor(rH))
            iW = int(math.floor(rW))

            sH = rH - iH
            sW = rW - iW

            if iH < 0 or inH - 1 <= iH or iW < 0 or inW - 1 <= iW:
                tmpImage[i][j] = 255
            else:
                C1 = float(inImage[iH][iW])
                C2 = float(inImage[iH][iW + 1])
                C3 = float(inImage[iH + 1][iW + 1])
                C4 = float(inImage[iH + 1][iW])

                tmpImage[i][j] = int(C1 * (1 - sH) * (1 - sW) + C2 * sW
                                     * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH)

    # 회전
    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = 0

    cx = tmpH // 2
    cy = tmpW // 2

    for i in range(outH):
        for j in range(outW):
            xd = i
            yd = j

            xs = int(math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy))
            ys = int(-math.sin(radian) * (xd - cx) + math.cos(radian) * (yd - cy))

            xs += cx
            ys += cy

            if (0 <= xs and xs < outH) and (0 <= ys and ys < outW):
                outImage[xd][yd] = tmpImage[xs][ys]
    #############################

    displayImage()

def mirrorVer(): # 미러링(상하)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            outImage[i][j] = inImage[inH - 1 - i][j]
    #############################

    displayImage()

def mirrorHor(): # 미러링(좌우)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            outImage[i][j] = inImage[i][inH - 1 - j]
    #############################

    displayImage()

def move():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    posH = askinteger('정수 입력', '이동할 Height')
    # 취소1
    if posH is None:
        return

    posW = askinteger('정수 입력', '이동할 Width')
    # 취소2
    if posW is None:
        return

    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = 0

    for i in range(inH - posH):
        for j in range(inW - posW):
            nx = i + posH
            ny = j + posW

            if (0 <= nx and nx < outH) and (0 <= ny and ny < outW):
                outImage[nx][ny] = inImage[i][j]
    #############################

    displayImage()

def morphing(): # 모핑 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = tmpH = inH
    outW = tmpW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpImage = malloc2D(tmpH, tmpW)

    ## 모핑할 이미지 불러오기 ##
    fullname = askopenfilename(parent=window, filetypes=(('RAW파일', '*.raw'), ('모든 파일', '*.*')))

    # 취소
    if fullname == '':
        return

    # 중요! 입력 이미지 크기를 결정
    fsize = os.path.getsize(fullname)  # 파일 크기(Byte)
    tmpH = tmpW = int(math.sqrt(fsize))

    # 파일 --> 메모리
    rfp = open(fullname, 'rb')
    for i in range(tmpH):
        for j in range(tmpW):
            tmpImage[i][j] = ord(rfp.read(1))

    rfp.close()

    #### 진짜 영상 처리 알고리즘 ####
    for i in range(inH):
        for j in range(inW):
            u = ((i * inH) + (j + 1.0)) / (inH * inW)
            tmp = (int)((1.0 - u) * inImage[i][j] + u * tmpImage[i][j])

            if 255 < tmp:
                outImage[i][j] = 255
            elif tmp < 0:
                outImage[i][j] = 0
            else:
                outImage[i][j] = int(tmp)
    #############################

    displayImage()

def histoStretch(): # 히스토그램 스트레칭
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    global inHisto, outHisto

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    high, low = inImage[0][0], inImage[0][0]

    for i in range(inH):
        for j in range(inW):
            if inImage[i][j] < low:
                low = inImage[i][j]

            if high < inImage[i][j]:
                high = inImage[i][j]

    for i in range(inH):
        for j in range(inW):
            old = inImage[i][j]
            new = int((old - low) / (high - low) * 255.0)

            if new < 0:
                new = 0

            if 255 < new:
                new = 255

            outImage[i][j] = new
    #############################

    displayImage()

    # 히스토그램 데이터
    inHisto = []
    outHisto = []

    for i in range(inH):
        inHisto += inImage[i]
        outHisto += outImage[i]

    histogramMenu.entryconfig('히스토그램 비교', state='normal')

def endIn(): # 앤드 인 탐색
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    global inHisto, outHisto

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    high, low = inImage[0][0], inImage[0][0]

    for i in range(inH):
        for j in range(inW):
            if inImage[i][j] < low:
                low = inImage[i][j]

            if high < inImage[i][j]:
                high = inImage[i][j]
    high -= 50
    low += 50

    for i in range(inH):
        for j in range(inW):
            old = inImage[i][j]
            new = int((old - low) / (high - low) * 255.0)

            if new < 0:
                new = 0

            if 255 < new:
                new = 255

            outImage[i][j] = new
    #############################

    displayImage()

    # 히스토그램 데이터
    inHisto = []
    outHisto = []

    for i in range(inH):
        inHisto += inImage[i]
        outHisto += outImage[i]

    histogramMenu.entryconfig('히스토그램 비교', state='normal')

def histoEqual(): # 히스토그램 평활화
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    global inHisto, outHisto

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    #1단계 : 빈도 수 세기 (=히스토그램)
    histo = [0 for _ in range(256)]

    for i in range(inH):
        for j in range(inW):
            histo[inImage[i][j]] += 1

    # 2단계 : 누적 히스토그램 생성
    sumHisto = [0 for _ in range(256)]
    sumHisto[0] = histo[0]

    for i in range(1, 256, 1):
        sumHisto[i] = sumHisto[i - 1] + histo[i]

    # 3단계 : 정규화된 히스토그램 생성
    normalHisto = [0.0 for _ in range(256)]

    for i in range(256):
        normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0

    for i in range(inH):
        for j in range(inW):
            outImage[i][j] = int(normalHisto[inImage[i][j]])
    #############################

    displayImage()

    # 히스토그램 데이터
    inHisto = []
    outHisto = []

    for i in range(inH):
        inHisto += inImage[i]
        outHisto += outImage[i]

    histogramMenu.entryconfig('히스토그램 비교', state='normal')

def emboss(): # 엠보싱
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[-1.0, 0.0, 0.0],
             [0.0, 0.0, 0.0],
             [0.0, 0.0, 1.0]] # 엠보싱 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0 # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 후처리 (마스크 값의 합계에 따라서)
    for i in range(outH):
        for j in range(outW):
            tmpOutImage[i][j] += 127.0

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def blur(): # 블러링(3x3)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[1.0 / 9, 1.0 / 9, 1.0 / 9],
		[1.0 / 9, 1.0 / 9, 1.0 / 9],
		[1.0 / 9, 1.0 / 9, 1.0 / 9]] # 블러링 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0  # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def blur2(): # 블러링(9x9)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 8, inW + 8)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[0.0 for _ in range(9)] for _ in range(9)] # 블러링 마스크

    for i in range(9):
        for j in range(9):
            mask[i][j] = 1.0 / 81

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 8):
        for j in range(inW + 8):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 4][j + 4] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 9x9 곱하기
            S = 0.0  # 마스크 81개와 입력값 81개를 각각 곱해서 합한 값

            for m in range(9):
                for n in range(9):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def sharp(): # 샤프닝
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[0.0, -1.0, 0.0],
		[-1.0, 5.0, -1.0],
		[0.0, -1.0, 0.0]] # 샤프닝 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0  # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def sharpHf(): # 샤프닝(고주파)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[-1.0 / 9, -1.0 / 9, -1.0 / 9],
		[-1.0 / 9, 8.0 / 9, -1.0 / 9 ],
		[-1.0 / 9, -1.0 / 9, -1.0 / 9]] # 샤프닝(고주파) 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0  # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n] * 20

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def sharpLf(): # 샤프닝(저주파)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    alpha = askinteger('정수 입력', '알파 값')

    # 취소
    if alpha is None:
        return

    mask = [[1.0 / 9, 1.0 / 9, 1.0 / 9],
		[1.0 / 9, 1.0 / 9, 1.0 / 9],
		[1.0 / 9, 1.0 / 9, 1.0 / 9]] # 샤프닝(저주파) 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0  # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            unsharp = alpha * inImage[i][j] - tmpOutImage[i][j]

            if unsharp < 0.0:
                outImage[i][j] = 0
            elif 255.0 < unsharp:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(unsharp)
    #############################

    displayImage()

def gaussian(): # 가우시안
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[1.0 / 16, 1.0 / 8, 1.0 / 16],
		[1.0 / 8, 1.0 / 4, 1.0 / 8],
		[1.0 / 16, 1.0 / 8, 1.0 / 16]] # 가우시안 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0  # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def edgeVer(): # 경계선(수직)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[0.0, 0.0, 0.0],
		[-1.0, 1.0, 0.0],
		[0.0, 0.0, 0.0]] # 수직 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0  # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def edgeHor(): # 경계선(수평)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[0.0, -1.0, 0.0],
		[0.0, 1.0, 0.0],
		[0.0, 0.0, 0.0]] # 수평 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            # 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
            S = 0.0  # 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def edgeHomogen(): # 경계선(유사 연산자)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S = 0.0

            for m in range(3):
                for n in range(3):
                    if S < math.fabs(tmpInImage[i + 1][j + 1] - tmpInImage[i + m][j + n]):
                        S = math.fabs(tmpInImage[i + 1][j + 1] - tmpInImage[i + m][j + n])

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def edgeDiff(): # 경계선(차 연산자)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S = 0.0

            for n in range(3):
                if  S < math.fabs(tmpInImage[i][j + n] - tmpInImage[i + 2][j - n + 2]):
                    S = math.fabs(tmpInImage[i][j + n] - tmpInImage[i + 2][j + -n + 2])

            if S < math.fabs(tmpInImage[i + 1][j + 2] - tmpInImage[i + 1][j]):
                S = math.fabs(tmpInImage[i + 1][j + 2] - tmpInImage[i + 1][j])

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def edgeRoberts(): # 경계선 1차 미분 (로버츠)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpRowInImage = malloc2D(inH + 2, inW + 2)
    tmpColInImage = malloc2D(inH + 2, inW + 2)
    tmpRowOutImage = malloc2D(outH, outW)
    tmpColOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    maskRow = [[-1.0, 0.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, 0.0, 0.0]] # 로버츠 행 에지 검출 마스크

    maskCol = [[0.0, 0.0, -1.0],
		[0.0, 1.0, 0.0],
        [0.0, 0.0, 0.0]] # 로버츠 열 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpRowInImage[i][j] = tmpColInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S1 = S2 = 0.0

            for m in range(3):
                for n in range(3):
                    S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n]
                    S2 += tmpColInImage[i + m][j + n] * maskCol[m][n]

            tmpRowOutImage[i][j] = S1
            tmpColOutImage[i][j] = S2

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            S1 = tmpRowOutImage[i][j]
            S2 = tmpColOutImage[i][j]

            if math.sqrt(S1 * S1 + S2 * S2) < 0.0:
                outImage[i][j] = 0
            elif 255.0 < math.sqrt(S1 * S1 + S2 * S2):
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(math.sqrt(S1 * S1 + S2 * S2))
    #############################

    displayImage()

def edgePrewitt(): # 경계선 1차 미분(프리윗)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpRowInImage = malloc2D(inH + 2, inW + 2)
    tmpColInImage = malloc2D(inH + 2, inW + 2)
    tmpRowOutImage = malloc2D(outH, outW)
    tmpColOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    maskRow = [[-1.0, -1.0, -1.0],
		[0.0, 0.0, 0.0],
		[1.0, 1.0, 1.0]] # 프리윗 행 에지 검출 마스크

    maskCol = [[1.0, 0.0, -1.0],
		[1.0, 0.0, -1.0],
		[1.0, 0.0, -1.0]] # 프리윗 열 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpRowInImage[i][j] = tmpColInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S1 = S2 = 0.0

            for m in range(3):
                for n in range(3):
                    S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n]
                    S2 += tmpColInImage[i + m][j + n] * maskCol[m][n]

            tmpRowOutImage[i][j] = S1
            tmpColOutImage[i][j] = S2

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            S1 = tmpRowOutImage[i][j]
            S2 = tmpColOutImage[i][j]

            if math.sqrt(S1 * S1 + S2 * S2) < 0.0:
                outImage[i][j] = 0
            elif 255.0 < math.sqrt(S1 * S1 + S2 * S2):
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(math.sqrt(S1 * S1 + S2 * S2))
    #############################

    displayImage()

def edgeSobel(): # 경계선 1차 미분 (소벨)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpRowInImage = malloc2D(inH + 2, inW + 2)
    tmpColInImage = malloc2D(inH + 2, inW + 2)
    tmpRowOutImage = malloc2D(outH, outW)
    tmpColOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    maskRow = [[-1.0, -2.0, -1.0],
		[0.0, 0.0, 0.0],
		[1.0, 2.0, 1.0]] # 소벨 행 에지 검출 마스크

    maskCol = [[1.0, 0.0, -1.0],
		[2.0, 0.0, -2.0],
		[1.0, 0.0, -1.0]] # 소벨 열 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpRowInImage[i][j] = tmpColInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S1 = S2 = 0.0

            for m in range(3):
                for n in range(3):
                    S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n]
                    S2 += tmpColInImage[i + m][j + n] * maskCol[m][n]

            tmpRowOutImage[i][j] = S1
            tmpColOutImage[i][j] = S2

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            S1 = tmpRowOutImage[i][j]
            S2 = tmpColOutImage[i][j]

            if math.sqrt(S1 * S1 + S2 * S2) < 0.0:
                outImage[i][j] = 0
            elif 255.0 < math.sqrt(S1 * S1 + S2 * S2):
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(math.sqrt(S1 * S1 + S2 * S2))
    #############################

    displayImage()

def edgeLaplacian(): # 경계선 2차 미분 (라플라시안)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[0.0, -1.0, 0.0],
		[-1.0, 4.0, -1.0],
		[0.0, -1.0, 0.0]] # 라플라시안 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 1][j + 1] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S = 0.0

            for m in range(3):
                for n in range(3):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def edgeLoG(): # 경계선 2차 미분 (LoG)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 4, inW + 4)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask = [[0.0, 0.0, -1.0, 0.0, 0.0],
		[0.0, -1.0, -2.0, -1.0, 0.0],
		[-1.0, -2.0, 16.0, -2.0, -1.0],
		[0.0, -1.0, -2.0, -1.0, 0.0],
		[0.0, 0.0, -1.0, 0.0, 0.0]] # LoG 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 2):
        for j in range(inW + 2):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 2][j + 2] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S = 0.0

            for m in range(5):
                for n in range(5):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

def edgeDog(): # 경계선 2차 미분 (DoG)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)
    tmpInImage = malloc2D(inH + 6, inW + 6)
    tmpOutImage = malloc2D(outH, outW)

    #### 진짜 영상 처리 알고리즘 ####
    mask= [[0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0],
		[0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0],
		[-1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0],
		[-1.0, -3.0, 5.0, 16.0, 5.0, -3.0, -1.0],
		[-1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0],
		[0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0],
		[0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0]] # DoG 에지 검출 마스크

    # 임시 입력 메모리를 초기화(127) : 필요시 평균값
    for i in range(inH + 6):
        for j in range(inW + 6):
            tmpInImage[i][j] = 127

    # 입력 이미지 -> 임시 입력 이미지
    for i in range(inH):
        for j in range(inW):
            tmpInImage[i + 3][j + 3] = inImage[i][j]

    # ** 회선 연산
    for i in range(inH):
        for j in range(inW):
            S = 0.0

            for m in range(7):
                for n in range(7):
                    S += tmpInImage[i + m][j + n] * mask[m][n]

            tmpOutImage[i][j] = S

    # 임시 출력 영상 --> 출력 영상
    for i in range(outH):
        for j in range(outW):
            if tmpOutImage[i][j] < 0.0:
                outImage[i][j] = 0
            elif 255.0 < tmpOutImage[i][j]:
                outImage[i][j] = 255
            else:
                outImage[i][j] = int(tmpOutImage[i][j])
    #############################

    displayImage()

### 전역 변수부
window, canvas, paper = None, None, None
inImage, outImage = [], []
inH, inW, outH, outW = [0] * 4
fullname = ''
inHisto, outHisto = [], []

### 메인 코드부
window = Tk() # 벽
window.geometry('500x500')
window.resizable(width=False, height=False)
window.title('영상 처리 (Version 1)')

# 메뉴 만들기
mainMenu = Menu(window) # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu, tearoff=0) # 상위 메뉴 (파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=openImage)
fileMenu.add_command(label='저장', command=saveImage, state='disabled')
fileMenu.add_separator()
fileMenu.add_command(label='종료', command=onExit)

pixelMenu = Menu(mainMenu, tearoff=0) # 상위 메뉴 (화소 점 처리)
mainMenu.add_cascade(label='화소 점 처리', menu=pixelMenu, state='disabled')
pixelMenu.add_command(label='동일 이미지', command=equalImage)
brightnessMenu = Menu(pixelMenu, tearoff=0) # 추가 메뉴 (밝기 변경)
pixelMenu.add_cascade(label='밝기 변경', menu=brightnessMenu)
brightnessMenu.add_command(label='밝게/어둡게', command=addImage)
brightnessMenu.add_command(label='더 밝게/어둡게', command=mulImage)
pixelMenu.add_separator()
pixelMenu.add_command(label='AND', command=andImage)
pixelMenu.add_command(label='OR', command=orImage)
pixelMenu.add_command(label='XOR', command=xorImage)
pixelMenu.add_command(label='NOT', command=notImage)
pixelMenu.add_separator()
pixelMenu.add_command(label='감마', command=gammaImage)
parabolaMenu = Menu(pixelMenu, tearoff=0) # 추가 메뉴 (파라볼라)
pixelMenu.add_cascade(label='파라볼라', menu=parabolaMenu)
parabolaMenu.add_command(label='CAP', command=parabolaCapImage)
parabolaMenu.add_command(label='CUP', command=parabolaCupImage)
pixelMenu.add_command(label='포스터라이징', command=posterizing)
pixelMenu.add_command(label='강조', command=stressImage)
bwMenu = Menu(pixelMenu, tearoff=0) # 추가 메뉴 (흑백)
pixelMenu.add_cascade(label='흑백', menu=bwMenu)
bwMenu.add_command(label='기본', command=bwImage)
bwMenu.add_command(label='평균값', command=bwAvgImage)
bwMenu.add_command(label='중앙값', command=bwMedImage)

geometryMenu = Menu(mainMenu, tearoff=0) # 상위 메뉴 (기하학 처리)
mainMenu.add_cascade(label='기하학 처리', menu=geometryMenu, state='disabled')
zoomOutMenu = Menu(geometryMenu, tearoff=0) # 추가 메뉴 (축소)
geometryMenu.add_cascade(label='축소', menu=zoomOutMenu)
zoomOutMenu.add_command(label='기본', command=zoomOut)
zoomOutMenu.add_command(label='평균값', command=zoomOutAvg)
zoomOutMenu.add_command(label='중앙값', command=zoomOutMed)
zoomInMenu = Menu(geometryMenu, tearoff=0) # 추가 메뉴 (확대)
geometryMenu.add_cascade(label='확대', menu=zoomInMenu)
zoomInMenu.add_command(label='포워딩', command=zoomIn1)
zoomInMenu.add_command(label='백워딩', command=zoomIn2)
zoomInMenu.add_command(label='양선형 보간', command=zoomInBilinear)
rotateMenu = Menu(geometryMenu, tearoff=0) # 추가 메뉴 (회전)
geometryMenu.add_cascade(label='회전', menu=rotateMenu)
rotateMenu.add_command(label='기본', command=rotate)
rotateMenu.add_command(label='중앙 & 백워딩', command=rotate2)
rotateMenu.add_command(label='확대', command=rotateZoomIn)
rotateMenu.add_command(label='확대 & 양선형', command=rotateZoomInBilinear)
mirrorMenu = Menu(geometryMenu, tearoff=0) # 추가 메뉴 (미러링)
geometryMenu.add_cascade(label='미러링', menu=mirrorMenu)
mirrorMenu.add_command(label='상하', command=mirrorVer)
mirrorMenu.add_command(label='좌우', command=mirrorHor)
geometryMenu.add_command(label='이동', command=move)
geometryMenu.add_command(label='모핑', command=morphing)

histogramMenu = Menu(mainMenu, tearoff=0) # 상위 메뉴 (히스토그램 처리)
mainMenu.add_cascade(label='히스토그램 처리', menu=histogramMenu, state='disabled')
histogramMenu.add_command(label='스트레칭', command=histoStretch)
histogramMenu.add_command(label='endIn', command=endIn)
histogramMenu.add_command(label='평활화', command=histoEqual)
histogramMenu.add_separator()
histogramMenu.add_command(label='히스토그램 비교', command=makeHistGraph, state='disabled')

areaMenu = Menu(mainMenu, tearoff=0) # 상위 메뉴 (영역 처리)
mainMenu.add_cascade(label='영역 처리', menu=areaMenu, state='disabled')
areaMenu.add_command(label='엠보싱', command=emboss)
blurMenu = Menu(areaMenu, tearoff=0) # 추가 메뉴 (블러링)
areaMenu.add_cascade(label='블러링', menu=blurMenu)
blurMenu.add_command(label='3x3', command=blur)
blurMenu.add_command(label='9x9', command=blur2)
sharpMenu = Menu(areaMenu, tearoff=0) # 추가 메뉴 (샤프닝)
areaMenu.add_cascade(label='샤프닝', menu=sharpMenu)
sharpMenu.add_command(label='기본', command=sharp)
sharpMenu.add_command(label='고주파', command=sharpHf)
sharpMenu.add_command(label='저주파', command=sharpLf)
areaMenu.add_command(label='가우시안', command=gaussian)
edgeMenu = Menu(areaMenu, tearoff=0) # 추가 메뉴 (경계선)
areaMenu.add_cascade(label='경계선', menu=edgeMenu)
sdMenu = Menu(edgeMenu, tearoff=0) # 추가 메뉴 (이동과 차분)
edgeMenu.add_cascade(label='이동과 차분', menu=sdMenu)
sdMenu.add_command(label='수직', command=edgeVer)
sdMenu.add_command(label='수평', command=edgeHor)
operatorMenu = Menu(edgeMenu, tearoff=0) # 추가 메뉴 (연산자)
edgeMenu.add_cascade(label='연산자', menu=operatorMenu)
operatorMenu.add_command(label='유사 연산자', command=edgeHomogen)
operatorMenu.add_command(label='차 연산자', command=edgeDiff)
fdeMenu = Menu(edgeMenu, tearoff=0) # 추가 메뉴 (1차 미분)
edgeMenu.add_cascade(label='1차 미분', menu=fdeMenu)
fdeMenu.add_command(label='로버츠', command=edgeRoberts)
fdeMenu.add_command(label='프리윗', command=edgePrewitt)
fdeMenu.add_command(label='소벨', command=edgeSobel)
sdeMenu = Menu(edgeMenu, tearoff=0) # 추가 메뉴 (2차 미분)
edgeMenu.add_cascade(label='2차 미분', menu=sdeMenu)
sdeMenu.add_command(label='라플라시안', command=edgeLaplacian)
sdeMenu.add_command(label='LoG', command=edgeLoG)
sdeMenu.add_command(label='DoG', command=edgeDog)

window.protocol('WM_DELETE_WINDOW', onExit)
window.mainloop()