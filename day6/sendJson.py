import requests, json, base64

while(1):
	url = "http://127.0.0.1:12345/"
	with open('a.png', 'rb') as f:
	 pic = f.read()
	
	print(len(base64.b64encode(pic).decode()))
	headers = {"Content-Type": "application/json"}
	data = {
	  "app_key": "13c1815dbca2413c2db75b5ac50349f4e1dd9786",
	  "file": base64.b64encode(pic).decode(),
	  # 下列项可以改为需要的阈值
	  'facepose': "40",  # 人脸是正对镜头(姿态)
	  'eyegaze': "40",  # 视线是否正常
	  'eyeskew': "35",  # 眼睛是否歪斜(双眼连线不水平)
	  'shoulderskew': "20",  # 肩膀是否水平正对镜头
	  'darkillum': "50",  # 照片光照是否昏暗
	  'unbalanceillum': "50",  # 人脸是否为阴阳脸
	  'bfsimilarity': "60",  # 衣服和背景颜色是否相似
	}
	data_json = json.dumps(data)
	response = requests.post(url, headers=headers, data=data_json)
	print(response.text)
	#break
