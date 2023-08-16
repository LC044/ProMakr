// let ul = document.getElementById('write');
let write = document.getElementById('write');
function add(html){
    // let li1 = document.createElement("li");
    let text1 = document.createTextNode(html);
    // li1.appendChild(text1);
    // write.append(html);
    write.append(text1)
    // document.write("You are learning how to call JavaScript function in html");
    // alert("Hello");
}

//接收变量处理函数
var updateattribute=function(text)
{
    $("#attrid").val(text);
}

new QWebChannel(qt.webChannelTransport,function(channel){
    var webobj = channel.objects.webobj;
    window.foo = webobj;
    webobj.someattributeChanged.connect(updateattribute);  //接收C++传递过来的数据的处理接口
});
