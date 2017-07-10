

var widget49020 = {};
widget49020.scriptUrl = "http://api.content.ad/Scripts/widget2.aspx?id=c03478c3-a51b-4098-9725-b6eb836f430c&d=d2F2c291cmNlLmNvbQ%3D%3D&wid=49020&cb=1487857033557";

widget49020.readCookie = function (name) {
    var nameWithEqual = name + "=";
    var params = document.cookie.split(';');
    for(var i = 0; i < params.length; i++) {
        var nameValuePair = params[i];
        while (nameValuePair.charAt(0) == ' ') nameValuePair = nameValuePair.substring(1, nameValuePair.length);
        if (nameValuePair.indexOf(nameWithEqual) == 0) return nameValuePair.substring(nameWithEqual.length, nameValuePair.length);
    }
    return null;
};

widget49020.updateSourceCookie = function (name, value) {
    var d = new Date();
    d.setTime(d.getTime() + (30*60*1000));
    document.cookie = name + "=" + value + ";path=/;expires=" + d.toUTCString();
};

widget49020.params = (function () {
    var result = {}, queryString = widget49020.scriptUrl.substring(widget49020.scriptUrl.indexOf("id=")), re = /([^&=]+)=([^&]*)/g, m;
    while (m = re.exec(queryString)) {
        result[decodeURIComponent(m[1])] = decodeURIComponent(m[2]);
    }

    var scriptUrlFromDomain = widget49020.scriptUrl.substr(widget49020.scriptUrl.indexOf("://") + 3);
    var server = scriptUrlFromDomain.substr(0, scriptUrlFromDomain.indexOf("/"));
    var url = result["url"] ? decodeURIComponent(result["url"]) : decodeURIComponent(window.location);
    
    result["lazyLoad"] = (result["lazyLoad"] == true ? true : false);
    result["server"] = (result["test"] == true ? "test." + server : server);
    result["title"] = (result["title"] ? result["title"] : encodeURI(escape(document.title)));
    result["url"] = encodeURIComponent(url);

    if (result["pre"] != undefined) {
        result["pre"] = encodeURIComponent(result["pre"]);
    }

    if (result["clientId"] === undefined && result["clientId2"] === undefined) {
        var pageParams = {}, pageQueryString = url.substring(url.indexOf("?")+1), pm;
	    while (pm = re.exec(pageQueryString)) {
	        pageParams[decodeURIComponent(pm[1])] = decodeURIComponent(pm[2]);
	    }
	    
	    var source = widget49020.readCookie("source");
	    var campaign = widget49020.readCookie("campaign");
        if (pageParams["utm_source"] !== undefined && pageParams["utm_source"] !== "") {
            if (pageParams["utm_source"] !== source) {
                widget49020.updateSourceCookie("source", pageParams["utm_source"]);
            }
            result["clientId"] = pageParams["utm_source"];
        } else if (source !== null && source !== "") {
            result["clientId"] = source;
        }

        if (pageParams["utm_campaign"] !== undefined && pageParams["utm_campaign"] !== "") {
            if (pageParams["utm_campaign"] !== campaign) {
                widget49020.updateSourceCookie("campaign", pageParams["utm_campaign"]);
            }
            result["clientId2"] = pageParams["utm_campaign"];
        } else if (campaign !== null && campaign !== "") {
            result["clientId2"] = campaign;
        }
    }
    return result;
} ());

widget49020.paramList = [];
for (var key in widget49020.params) {
    widget49020.paramList.push(key + '=' + widget49020.params[key]);
}

widget49020.widgetUrl = (location.protocol === 'https:' ? 'https:' : 'http:') + "//" + widget49020.params.server + "/GetWidget.aspx?" + widget49020.paramList.join('&');
widget49020.isLoaded = false;

widget49020.init = function (widgetId, widgetUrl, lazyLoad, loadMultiple) {
    if (typeof (window["contentAd" + widgetId]) == 'undefined') {
        if (!widget49020.isLoaded) {
            widget49020.isLoaded = true;
            if (lazyLoad) {
                (function () {
                    function asyncLoad() {
                        var s = document.createElement('script');
                        s.type = 'text/javascript';
                        s.async = true;
                        s.src = widgetUrl;
                        var x = document.getElementsByTagName('script')[0];
                        x.parentNode.insertBefore(s, x);
                    }
                    if (window.attachEvent)
                        window.attachEvent('onload', asyncLoad);
                    else
                        window.addEventListener('load', asyncLoad, false);
                })();
            } else {
                (function () {
                    var s = document.createElement('script');
                    s.type = 'text/javascript';
                    s.async = true;
                    s.src = widgetUrl;
                    var x = document.getElementsByTagName('script')[0];
                    x.parentNode.insertBefore(s, x);
                })();
            }
        }
        setTimeout(function () { widget49020.init(widgetId, widgetUrl, lazyLoad, loadMultiple) }, 50);
    } else {
        var content = window["contentAd" + widgetId]();
        var container = document.getElementById("contentad" + widgetId);
        var newDiv = document.createElement("div");
        newDiv.innerHTML = content;
        if (container === undefined || container === null) {
            var scripts = document.getElementsByTagName("script");
		    for (var i = 0; i < scripts.length; i++) {
			    if (scripts[i].innerHTML.indexOf("c03478c3-a51b-4098-9725-b6eb836f430c") !== -1) {
			        scripts[i].parentNode.insertBefore(newDiv, scripts[i]);
			    }
	        }
        } else {            
            container.parentNode.insertBefore(newDiv, container);
        }
        
        if (typeof (window["initJQuery" + widgetId]) != 'undefined') {
            window["initJQuery" + widgetId]();
        }
        if (loadMultiple) {
            window["contentAd" + widgetId] = undefined;
        }
    }
};

widget49020.updatePopCookie = function () {
    if (document.cookie.indexOf("popdays") == -1) {
        var d = new Date();
        if (widget49020.params.exitPopExpireDays === undefined) {
            widget49020.params.exitPopExpireDays = 0;
            d.setTime(d.getTime() + (30*60*1000));
        } else {
            d.setTime(d.getTime() + (widget49020.params.exitPopExpireDays*24*60*60*1000));
        }
        document.cookie = "popdays=" + widget49020.params.exitPopExpireDays + ";path=/;expires=" + d.toUTCString();

        widget49020.init(widget49020.params.wid, widget49020.widgetUrl, widget49020.params.lazyLoad, widget49020.params.loadMultiple);
    } else {
        if (widget49020.params.exitPopExpireDays > 0 && widget49020.readCookie("popdays") != widget49020.params.exitPopExpireDays) {
            var d = new Date();
            d.setTime(d.getTime() + (widget49020.params.exitPopExpireDays*24*60*60*1000));
            document.cookie = "popdays=" + widget49020.params.exitPopExpireDays + ";path=/;expires=" + d.toUTCString();
        } else if (widget49020.params.exitPopExpireDays <= 0) {
            document.cookie = "popdays=-1;path=/;expires=Thu, 01 Jan 1970 00:00:01 GMT";
            widget49020.init(widget49020.params.wid, widget49020.widgetUrl, widget49020.params.lazyLoad, widget49020.params.loadMultiple);
        } else if (widget49020.params.exitPopExpireDays === undefined && widget49020.readCookie("popdays") > 0) {
            var d = new Date();
            d.setTime(d.getTime() + (30*60*1000));
            document.cookie = "popdays=0;path=/;expires=" + d.toUTCString();
        }
    }
};

widget49020.scrollChange = function () {
    var totalHeight, currentScroll, visibleHeight;
      
    if (document.documentElement.scrollTop) {
        currentScroll = document.documentElement.scrollTop;
    } else { 
        currentScroll = document.body.scrollTop;
    }
      
    totalHeight = document.body.offsetHeight;
    visibleHeight = window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight;
    var tempScroll = currentScroll + visibleHeight;
    var atEndOfPage = totalHeight <= tempScroll + (totalHeight * 0.10);
    var isScrollingUp = tempScroll < widget49020.lowestScroll;
    var hasScrolledDown = widget49020.lowestScroll > 100;
    
    if (widget49020.lowestScroll === undefined || tempScroll > widget49020.lowestScroll) {
        widget49020.lowestScroll = tempScroll;
    }

    if ((atEndOfPage || (hasScrolledDown && isScrollingUp)) && !widget49020.isLoaded) {
        widget49020.updatePopCookie();
    }
};

widget49020.mouseCoordinates = function (e) {
    var tempX = 0, tempY = 0;

    if (!e) var e = window.event;
    tempX = e.clientX;
    tempY = e.clientY;
        
    if (tempX < 0) tempX = 0;
    if (tempY < 0) tempY = 0;
    
    if (widget49020.lowestY === undefined || tempY > widget49020.lowestY) {
        widget49020.lowestY = tempY;
    }
    
    if (tempY <= 20 && tempY < widget49020.lowestY && widget49020.lowestY > 100 && !widget49020.isLoaded) {
        widget49020.updatePopCookie();
    }
};

widget49020.exitPopMobile = false;
if (widget49020.params.exitPopMobile === 'true' || widget49020.params.exitPopMobile === '1') {
    widget49020.exitPopMobile = true;
    var touchEnabled = ('ontouchstart' in window) || (window.DocumentTouch && document instanceof DocumentTouch);
    var isMobile = false;
    if (navigator.userAgent !== undefined) {
        var userAgent = navigator.userAgent.toLowerCase();
        var iPhoneIndex = userAgent.indexOf("iphone");
        var iPadIndex = userAgent.indexOf("ipad");
        var isIPhone = (iPhoneIndex !== -1 && iPadIndex === -1) || (iPhoneIndex !== -1 && iPhoneIndex < iPadIndex);
        var isAndroid = userAgent.indexOf("android") !== -1 && userAgent.indexOf("mobile") !== -1;
        var isOtherMobile = userAgent.match(/^.*?(ipod|blackberry|mini|windows\\sce|palm|phone|mobile|smartphone|iemobile).*?$/) != null;
        isMobile = isIPhone || isAndroid || isOtherMobile;
    }
    
    if (touchEnabled && isMobile) {
        setInterval(widget49020.scrollChange, 50);
    }
}

widget49020.exitPop = false;
if (widget49020.params.exitPop === 'true' || widget49020.params.exitPop === '1') {
    widget49020.exitPop = true;
    if (widget49020.params.exitPopExpireDays === undefined && widget49020.readCookie("popdays") == 0) {
        var d = new Date();
        d.setTime(d.getTime() + (30*60*1000));
        document.cookie = "popdays=0;path=/;expires=" + d.toUTCString();
    }
    var isInternetExplorer = document.all ? true : false;
    if (!isInternetExplorer) document.captureEvents(Event.MOUSEMOVE);
    try {
        document.addEventListener('mousemove', widget49020.mouseCoordinates, false);
    } catch (e) {
        document.attachEvent('onmousemove', widget49020.mouseCoordinates);
    } finally {
        try {
            if (document.onmousemove) {
                var oldOnMouseMove = document.onmousemove;
                document.onmousemove = function(e) {
                    oldOnMouseMove(e);
                    widget49020.mouseCoordinates(e);
                };
            } else {
                document.onmousemove = function(e) {
                   widget49020.mouseCoordinates(e);
                };
            }
        } catch(e) {
        
        }
    }
} 

if (!widget49020.exitPop && !widget49020.exitPopMobile) {
    widget49020.init(widget49020.params.wid, widget49020.widgetUrl, widget49020.params.lazyLoad, widget49020.params.loadMultiple);
}