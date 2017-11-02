

var widget146410 = {};
widget146410.scriptUrl = "http://api.content.ad/Scripts/widget2.aspx?id=d6f7e909-a8c1-447b-bdf0-2611789903b5&d=d2F2c291cmNlLmNvbQ%3D%3D&wid=146410&exitPop=true&cb=1487857033309";

widget146410.readCookie = function (name) {
    var nameWithEqual = name + "=";
    var params = document.cookie.split(';');
    for(var i = 0; i < params.length; i++) {
        var nameValuePair = params[i];
        while (nameValuePair.charAt(0) == ' ') nameValuePair = nameValuePair.substring(1, nameValuePair.length);
        if (nameValuePair.indexOf(nameWithEqual) == 0) return nameValuePair.substring(nameWithEqual.length, nameValuePair.length);
    }
    return null;
};

widget146410.updateSourceCookie = function (name, value) {
    var d = new Date();
    d.setTime(d.getTime() + (30*60*1000));
    document.cookie = name + "=" + value + ";path=/;expires=" + d.toUTCString();
};

widget146410.params = (function () {
    var result = {}, queryString = widget146410.scriptUrl.substring(widget146410.scriptUrl.indexOf("id=")), re = /([^&=]+)=([^&]*)/g, m;
    while (m = re.exec(queryString)) {
        result[decodeURIComponent(m[1])] = decodeURIComponent(m[2]);
    }

    var scriptUrlFromDomain = widget146410.scriptUrl.substr(widget146410.scriptUrl.indexOf("://") + 3);
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
	    
	    var source = widget146410.readCookie("source");
	    var campaign = widget146410.readCookie("campaign");
        if (pageParams["utm_source"] !== undefined && pageParams["utm_source"] !== "") {
            if (pageParams["utm_source"] !== source) {
                widget146410.updateSourceCookie("source", pageParams["utm_source"]);
            }
            result["clientId"] = pageParams["utm_source"];
        } else if (source !== null && source !== "") {
            result["clientId"] = source;
        }

        if (pageParams["utm_campaign"] !== undefined && pageParams["utm_campaign"] !== "") {
            if (pageParams["utm_campaign"] !== campaign) {
                widget146410.updateSourceCookie("campaign", pageParams["utm_campaign"]);
            }
            result["clientId2"] = pageParams["utm_campaign"];
        } else if (campaign !== null && campaign !== "") {
            result["clientId2"] = campaign;
        }
    }
    return result;
} ());

widget146410.paramList = [];
for (var key in widget146410.params) {
    widget146410.paramList.push(key + '=' + widget146410.params[key]);
}

widget146410.widgetUrl = (location.protocol === 'https:' ? 'https:' : 'http:') + "//" + widget146410.params.server + "/GetWidget.aspx?" + widget146410.paramList.join('&');
widget146410.isLoaded = false;

widget146410.init = function (widgetId, widgetUrl, lazyLoad, loadMultiple) {
    if (typeof (window["contentAd" + widgetId]) == 'undefined') {
        if (!widget146410.isLoaded) {
            widget146410.isLoaded = true;
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
        setTimeout(function () { widget146410.init(widgetId, widgetUrl, lazyLoad, loadMultiple) }, 50);
    } else {
        var content = window["contentAd" + widgetId]();
        var container = document.getElementById("contentad" + widgetId);
        var newDiv = document.createElement("div");
        newDiv.innerHTML = content;
        if (container === undefined || container === null) {
            var scripts = document.getElementsByTagName("script");
		    for (var i = 0; i < scripts.length; i++) {
			    if (scripts[i].innerHTML.indexOf("d6f7e909-a8c1-447b-bdf0-2611789903b5") !== -1) {
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

widget146410.updatePopCookie = function () {
    if (document.cookie.indexOf("popdays") == -1) {
        var d = new Date();
        if (widget146410.params.exitPopExpireDays === undefined) {
            widget146410.params.exitPopExpireDays = 0;
            d.setTime(d.getTime() + (30*60*1000));
        } else {
            d.setTime(d.getTime() + (widget146410.params.exitPopExpireDays*24*60*60*1000));
        }
        document.cookie = "popdays=" + widget146410.params.exitPopExpireDays + ";path=/;expires=" + d.toUTCString();

        widget146410.init(widget146410.params.wid, widget146410.widgetUrl, widget146410.params.lazyLoad, widget146410.params.loadMultiple);
    } else {
        if (widget146410.params.exitPopExpireDays > 0 && widget146410.readCookie("popdays") != widget146410.params.exitPopExpireDays) {
            var d = new Date();
            d.setTime(d.getTime() + (widget146410.params.exitPopExpireDays*24*60*60*1000));
            document.cookie = "popdays=" + widget146410.params.exitPopExpireDays + ";path=/;expires=" + d.toUTCString();
        } else if (widget146410.params.exitPopExpireDays <= 0) {
            document.cookie = "popdays=-1;path=/;expires=Thu, 01 Jan 1970 00:00:01 GMT";
            widget146410.init(widget146410.params.wid, widget146410.widgetUrl, widget146410.params.lazyLoad, widget146410.params.loadMultiple);
        } else if (widget146410.params.exitPopExpireDays === undefined && widget146410.readCookie("popdays") > 0) {
            var d = new Date();
            d.setTime(d.getTime() + (30*60*1000));
            document.cookie = "popdays=0;path=/;expires=" + d.toUTCString();
        }
    }
};

widget146410.scrollChange = function () {
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
    var isScrollingUp = tempScroll < widget146410.lowestScroll;
    var hasScrolledDown = widget146410.lowestScroll > 100;
    
    if (widget146410.lowestScroll === undefined || tempScroll > widget146410.lowestScroll) {
        widget146410.lowestScroll = tempScroll;
    }

    if ((atEndOfPage || (hasScrolledDown && isScrollingUp)) && !widget146410.isLoaded) {
        widget146410.updatePopCookie();
    }
};

widget146410.mouseCoordinates = function (e) {
    var tempX = 0, tempY = 0;

    if (!e) var e = window.event;
    tempX = e.clientX;
    tempY = e.clientY;
        
    if (tempX < 0) tempX = 0;
    if (tempY < 0) tempY = 0;
    
    if (widget146410.lowestY === undefined || tempY > widget146410.lowestY) {
        widget146410.lowestY = tempY;
    }
    
    if (tempY <= 20 && tempY < widget146410.lowestY && widget146410.lowestY > 100 && !widget146410.isLoaded) {
        widget146410.updatePopCookie();
    }
};

widget146410.exitPopMobile = false;
if (widget146410.params.exitPopMobile === 'true' || widget146410.params.exitPopMobile === '1') {
    widget146410.exitPopMobile = true;
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
        setInterval(widget146410.scrollChange, 50);
    }
}

widget146410.exitPop = false;
if (widget146410.params.exitPop === 'true' || widget146410.params.exitPop === '1') {
    widget146410.exitPop = true;
    if (widget146410.params.exitPopExpireDays === undefined && widget146410.readCookie("popdays") == 0) {
        var d = new Date();
        d.setTime(d.getTime() + (30*60*1000));
        document.cookie = "popdays=0;path=/;expires=" + d.toUTCString();
    }
    var isInternetExplorer = document.all ? true : false;
    if (!isInternetExplorer) document.captureEvents(Event.MOUSEMOVE);
    try {
        document.addEventListener('mousemove', widget146410.mouseCoordinates, false);
    } catch (e) {
        document.attachEvent('onmousemove', widget146410.mouseCoordinates);
    } finally {
        try {
            if (document.onmousemove) {
                var oldOnMouseMove = document.onmousemove;
                document.onmousemove = function(e) {
                    oldOnMouseMove(e);
                    widget146410.mouseCoordinates(e);
                };
            } else {
                document.onmousemove = function(e) {
                   widget146410.mouseCoordinates(e);
                };
            }
        } catch(e) {
        
        }
    }
} 

if (!widget146410.exitPop && !widget146410.exitPopMobile) {
    widget146410.init(widget146410.params.wid, widget146410.widgetUrl, widget146410.params.lazyLoad, widget146410.params.loadMultiple);
}