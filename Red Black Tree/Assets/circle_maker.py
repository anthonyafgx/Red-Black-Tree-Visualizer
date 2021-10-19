from PIL import Image, ImageFont, ImageDraw



W, H = (64,64)
myFont = ImageFont.truetype(font="ARLRDBD.TTF", size=24)
text = 1

while(text < 256):
    
    redcircle = Image.open("blackcircle/0.png")
    draw = ImageDraw.Draw(redcircle)
    w, h = draw.textsize(str(text), font=myFont)

    draw.text(((W-w)/2, 18), str(text), font=myFont, fill="white")

    redcircle.save("blackcircle/" + str(text) + ".png", "PNG")

    text += 1
    
redcircle.close()
