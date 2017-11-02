document.write('<table border=0 style="border-spacing:0px"><tr><td height=280>');
document.write('<div style="text-align:center">');
document.write('<div id="contentad49020"><\/div>');
    (function(d) {
        var params =
        {
            id: "c03478c3-a51b-4098-9725-b6eb836f430c",
            d:  "d2F2c291cmNlLmNvbQ==",
            wid: "49020",
            cb: (new Date()).getTime()
        };

        var qs=[];
        for(var key in params) qs.push(key+'='+encodeURIComponent(params[key]));
        var s = d.createElement('script');s.type='text/javascript';s.async=true;
        var p = 'https:' == document.location.protocol ? 'https' : 'http';
        s.src = p + "://api.content.ad/Scripts/widget2.aspx?" + qs.join('&');
        d.getElementById("contentad49020").appendChild(s);
    })(document);
document.write('<\/div><\/td><\/tr><\/table>');
