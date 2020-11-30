# 安装
```
npm install -S --registry=http://47.96.88.190:4873
```

# 使用
align
```
const { Alignment,Type } = require("align");
const fs = require('fs');
const instance = new Alignment({
    auth_pack:Buffer.from(require('./auth_pack.json').auth_pack), 
    type:Type.ALIGN
});

(async () => {
    const version = instance.GetVersion();
    console.log("model version is ",version);
    const result = await instance.GetWordsTimeStamp(fs.readFileSync('./xxxxx.wav'), "xxxxx");
    console.log(result);
})()

```

# changelog
1. v1.0.12新增可选参数max_length,目前为限制引号(单/双)内的文本切分最大字数,后续会扩展为所有文本的最大切分字数,该规则受到其余规则影响不在所有情况下返回小于等于最大字数的切割单元,字幕换行仍然需要