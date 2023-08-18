let write = document.getElementById('write');
function add(html){
    console.log(html);
    let li1 = document.createElement("div");
    // let text1 = document.createTextNode(html);
    // li1.appendChild(text1);
    // li1.innerHTML = html;
    // write.append(html);
    // write.append(li1)
    write.innerHTML = html;
    // write.innerHTML = marked.parse(html);
    // document.write("You are learning how to call JavaScript function in html");
    // alert(html);
    // hljs.initHighlightingOnLoad();
    // hljs.initLineNumbersOnLoad();
    hljs.highlightAll();
}
