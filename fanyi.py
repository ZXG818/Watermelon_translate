'''
参考文章：
https://www.cnblogs.com/zhangboblogs/p/8542161.html
https://blog.csdn.net/levon2018/article/details/80343531
'''


#!/usr/bin/Python
# -*- coding: utf-8 -*-
import urllib.request
import json
import hashlib
import time
import random

def get_translation_result(value):
    #目标url
    target_url = 'http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule'

    #生成salt
    #源js文件： var t = "" + ((new Date).getTime() + parseInt(10 * Math.random(), 10));
    salt = int(time.time()*1000) + random.randint(0,10)

    #生成sign
    sign = hashlib.md5(("fanyideskweb" + value + str(salt) + "ebSeFb%=XZ%T[KZ)c(sy!").encode('utf-8')).hexdigest()

    #开始写Form data
    data = {}
    data['i'] = value      #要被翻译的字符串
    data['from'] = "AUTO"
    data['to'] = 'AUTO'
    data['smartResult'] = 'dict'
    data['client'] = 'fanyideskweb'
    data['salt'] = salt
    data['sign'] = sign
    data['doctype'] = 'json'
    data['version'] = '2.1'
    data['keyfrom'] = 'fanyi.web'
    data['action'] = 'FY_BY_REALTIME'
    data['typoResult'] = 'false'

    #转码
    data = urllib.parse.urlencode(data)

    #报头
    headers = {"Accept":"application/json, text/javascript, */*; q=0.01",
        #Accept-Encoding:gzip, deflate
        "Accept-Language":"zh-CN,zh;q=0.9",
        "Connection":"keep-alive",
        "Content-Length":len(data),
        "Content-Type":"application/x-www-form-urlencoded; charset=UTF-8",
        "Cookie":"OUTFOX_SEARCH_USER_ID_NCOO=1135910979.4269547; OUTFOX_SEARCH_USER_ID=-1364254390@10.168.1.8; fanyi-ad-id=40789; fanyi-ad-closed=1; JSESSIONID=aaafp6BJjIzwC4k7Mb5hw; ___rl__test__cookies=1520316265914",
        "Host":"fanyi.youdao.com",
        "Origin":"http://fanyi.youdao.com",
        "Referer":"http://fanyi.youdao.com/",
        "User-Agent":"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36",
        "X-Requested-With":"XMLHttpRequest"
    }
    req = urllib.request.Request(target_url,bytes(data,encoding = 'utf-8'),headers = headers)
    response = urllib.request.urlopen(req)
    content = response.read()
    content = content.decode('utf-8')

    #将字符串content用json库转换成字典result
    result = json.loads(content)
    #打印翻译后的结果
    return result['translateResult'][0][0]['tgt']
    











    
    
    
