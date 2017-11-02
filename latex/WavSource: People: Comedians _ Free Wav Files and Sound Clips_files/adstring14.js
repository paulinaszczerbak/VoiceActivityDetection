// one google ad will already have been generated.
// this code will create up to 2 more google ads, plus non-google ads if adnum>2, plus the exasin box if exasin!=0.

var jqhite = $('#innerT').height() + 2;
var LHite = $('#lowerHite').height() * 0.9146;
var totHite=Math.floor(jqhite+LHite);
if (totHite<=adhitefactor) {var h101=1;}
if (totHite>adhitefactor) {var h101=(totHite)/(adhitefactor+adspacehite);}
if (h101<1) {h101=1;}
var h102=Math.floor(h101);
var adnum=h102;
var h103=(h102*(adhitefactor+adspacehite))-adspacehite;

if (h103<jqhite) {
  if (h103 + adhitefactor + adspacehite < totHite) {
    adnum+=1;
    exasin=0;
  }
}

if (riteorleft==1) { $('').replaceAll( $('#TTTL') ); }  // moved this here from .htm files Aug 11, 2015

if (h103 + 280 + adspacehite >= totHite) {exasin=0;}

adnum=adnum-1;          // added these 2 lines after the 1st google ad was generated independently
if (adnum<0) {adnum=0;} // added these 2 lines after the 1st google ad was generated independently

// begin draw google ad in TLad div if adnum<2
if (adnum<2) {
var TLadstring='<p style="margin-bottom:22px"><script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"><\/script>'+
'<ins class="adsbygoogle" style="display:inline-block;width:970px;height:90px" data-ad-client="ca-pub-0780163802383173" data-ad-slot="4342201832"><\/ins>'+
'<script>'+
'(adsbygoogle = window.adsbygoogle || []).push(\{\})\;'+
'<\/script></p>'
$(TLadstring).replaceAll( $('#TLad') );
}
// end draw google ad in TLad div if adnum<2


if (adnum>0) {

var adstr = new Array (adnum);

if (adnum<=2) {var adnumc=adnum;} // if adnum<=2, then all tall ads are google
if (adnum>2) {var adnumc=2;}      // if adnum>2, then at least 1 tall ad is non-google 

// begin google ad code
for (c0=1; c0<=adnumc; c0++) {
adstr[c0-1]='<table border=0 cellspacing=0 cellpadding=0 style="width:'+String(tallwid[s]+tallmar)+'px; margin-bottom:'+String(adspacehite)+'px; margin-top:0px"><tr><td style="text-align:'+String(talllorr)+'; vertical-align:top">';
adstr[c0-1]+='<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"><\/script>';
adstr[c0-1]+='<ins class="adsbygoogle"'+
'     style="display:inline-block;width:'+String(tallwid[s])+'px;height:600px"'+
'     data-ad-client="ca-pub-0780163802383173"';
if (riteorleft==0 && s==0) {adstr[c0-1]+='     data-ad-slot="2774662235"></ins>';} // 160 left image
if (riteorleft==1 && s==0) {adstr[c0-1]+='     data-ad-slot="8681595038"></ins>';} // 160 right image
if (riteorleft==0 && s==1) {adstr[c0-1]+='     data-ad-slot="4111794635"></ins>';} // 120 left image
if (riteorleft==1 && s==1) {adstr[c0-1]+='     data-ad-slot="5448927033"></ins>';} // 120 right image
adstr[c0-1]+='<script>(adsbygoogle = window.adsbygoogle || []).push(\{\})\;<\/script></td></tr></table>';
} // end for c0=1
// end of google ad code



// below is the code for non-google ads, which will be drawn if adnum>2
if (adnum>2) {
if (s==0) {
var hyest=highest160;
var nGoo = [
// begin 0: amazon search
'<TABLE style="float:'+String(talllorr)+'; width:160px; height:600px" BORDER=0 CELLPADDING=1 cellspacing=0 BGCOLOR="#000000">'+
'<TR><TD><TABLE style="margin:auto; width:158px; height:598px" BORDER=0 CELLPADDING=4 cellspacing=0 BGCOLOR="#FFFFFF">'+
'<TR><TD COLSPAN=2 style="vertical-align:top; text-align:center" BGCOLOR="#000000">'+
'<IMG src="/logos/pdm-search-logo-126x32.gif" BORDER=0 title="In Association with Amazon.com" alt="">'+
'</TD></TR><TR><TD BGCOLOR="#FFFFFF" style="vertical-align:top; text-align:left" COLSPAN=2>'+
'<FORM METHOD="get" ACTION="http://www.amazon.com/exec/obidos/external-search" target="_blank">'+
'<font face="verdana,arial,helvetica" size="-2">'+
'<input type="radio" name="mode" value="blended" checked>All Products<br>'+
'<input type="radio" name="mode" value="books">Books<br>'+
'<input type="radio" name="mode" value="music">Popular Music<br>'+
'<input type="radio" name="mode" value="music-dd">Music Downloads<br>'+
'<input type="radio" name="mode" value="classical-music">Classical Music<br>'+
'<input type="radio" name="mode" value="dvd">DVD & Blu-ray<br>'+
'<input type="radio" name="mode" value="amazontv">Instant Video<br>'+
'<input type="radio" name="mode" value="pc-hardware">Computers<br>'+
'<input type="radio" name="mode" value="videogames">Computer Games<br>'+
'<input type="radio" name="mode" value="videogames">Video Games<br>'+
'<input type="radio" name="mode" value="electronics">Electronics<br>'+
'<input type="radio" name="mode" value="photo">Camera & Photo<br>'+
'<input type="radio" name="mode" value="gourmet">Gourmet Food<br>'+
'<input type="radio" name="mode" value="software">Software<br>'+
'<input type="radio" name="mode" value="toys">Toys & Games<br>'+
'<input type="radio" name="mode" value="tools">Tools & Hardware<br>'+
'<input type="radio" name="mode" value="garden">Outdoor Living<br>'+
'<input type="radio" name="mode" value="kitchen">Kitchen / Housewares<br>'+
'<input type="radio" name="mode" value="wireless-phones">Cell Phones & Service<br>'+
'<input type="radio" name="mode" value="magazines">Magazines<br>'+
'Search by keywords:<br>'+
'<INPUT TYPE="text" NAME="keyword" SIZE=13 VALUE="">'+
'<INPUT TYPE="hidden" NAME="tag" VALUE="wavsourcecom-20">'+
'<INPUT TYPE="hidden" NAME="sort" VALUE="review-rank">'+
'<INPUT TYPE="image" WIDTH=21 HEIGHT=21 BORDER=0 VALUE="Go" NAME="Go" src="/logos/pdm-search-go-btn.gif" ALIGN="absmiddle">'+
'</font></FORM>'+
'</TD></TR><TR><TD COLSPAN=2 style="vertical-align:top; text-align:center" BGCOLOR="#000000">'+
'<a href="http://www.amazon.com/exec/obidos/redirect-home/wavsourcecom-20" target="_blank"><IMG src="/logos/pdm-search-logo-126x32.gif" BORDER=0 ALT="In Association with Amazon.com"></a>'+
'</TD></TR></TABLE></TD></TR></TABLE>',
// begin 1: amazon-books
'<iframe name="amazon-books" id="amazon-books" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=bn1&mode=books&browse=1000&fc1=000000&lt1=_blank&lc1=3366FF&bg1=FFFFFF&f=ifr" marginwidth="0" marginheight="0" width="160" height="600" border="0" frameborder="0" style="border:none;" scrolling="no"></iframe>',
// begin 2: amazon-mens-mags
'<iframe name="amazon-mens-mags" id="amazon-mens-mags" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=bn1&mode=magazines&browse=602352&fc1=000000&lt1=_blank&lc1=3366FF&bg1=FFFFFF&f=ifr" marginwidth="0" marginheight="0" width="160" height="600" border="0" frameborder="0" style="border:none;" scrolling="no"></iframe>',
// begin 3: amazon-dvds
'<iframe name="amazon-dvds" id="amazon-dvds" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=bn1&mode=dvd&browse=130&fc1=000000&lt1=_blank&lc1=3366FF&bg1=FFFFFF&f=ifr" marginwidth="0" marginheight="0" width="160" height="600" border="0" frameborder="0" style="border:none;" scrolling="no"></iframe>',
// begin 4: amazon-instant-vids
'<iframe name="amazon-instant-vids" id="amazon-instant-vids" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=bn1&mode=amazontv&browse=16261631&fc1=000000&lt1=_blank&lc1=3366FF&bg1=FFFFFF&f=ifr" marginwidth="0" marginheight="0" width="160" height="600" border="0" frameborder="0" style="border:none;" scrolling="no"></iframe>',
// begin 5: amazon-kindle
'<iframe name="amazon-kindle" id="amazon-kindle" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=ur1&category=kindle&banner=1Z4BGFAR9ST7BT0409R2&f=ifr&lt1=_blank" width="160" height="600" scrolling="no" border="0" marginwidth="0" style="border:none;" frameborder="0"></iframe>',
// begin 6: amazon-gift-card
'<iframe name="amazon-gift-card" id="amazon-gift-card" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=ur1&category=gift_certificates&banner=0S32YAVKXXKQGNQSSGG2&lt1=_blank&f=ifr" width="160" height="600" scrolling="no" border="0" marginwidth="0" style="border:none;" frameborder="0"></iframe>',
// begin 7: amazon-prime1
'<iframe name="amazon-prime1" id="amazon-prime1" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=ur1&category=primeent&lt1=_blank&banner=1A1WA1TZ77GXJ3D2VDG2&f=ifr" width="160" height="600" scrolling="no" border="0" marginwidth="0" style="border:none;" frameborder="0"></iframe>',
// begin 8: amazon-prime2
'<iframe name="amazon-prime2" id="amazon-prime2" src="http://rcm-na.amazon-adsystem.com/e/cm?t=wavsourcecom-20&o=1&p=14&l=ur1&category=primeent&lt1=_blank&banner=07S5F1FYF67566B1GXR2&f=ifr" width="160" height="600" scrolling="no" border="0" marginwidth="0" style="border:none;" frameborder="0"></iframe>',
// begin 9: Zappos generic
'<a href="http://www.anrdoezrs.net/click-988367-10485802-1424977329000" target="_blank"><img src="http://www.tqlkg.com/image-988367-10485802-1424977329000" width="160" height="600" alt="" border="0"></a>',
// begin 10: The biggest gold clearance event. 60-80% off. expires 12-31-2019
'<a href="http://click.linksynergy.com/fs-bin/click?id=2GqXwp1ktwQ&offerid=328293.11&subid=0&type=4" TARGET="_BLANK"><IMG border="0" alt="Kohls Department Stores Inc" src="http://ad.linksynergy.com/fs-bin/show?id=2GqXwp1ktwQ&bids=328293.11&subid=0&type=4&gridnum=9"></a>',
// begin 11: Biggest gold star clearance. 60-80% off. plus free shipping with $50 purchase. expires 12-31-2019
'<a href="http://click.linksynergy.com/fs-bin/click?id=2GqXwp1ktwQ&offerid=328293.15&subid=0&type=4" TARGET="_BLANK"><IMG border=0 alt="Kohls Department Stores Inc" src="http://ad.linksynergy.com/fs-bin/show?id=2GqXwp1ktwQ&bids=328293.15&subid=0&type=4&gridnum=9"></a>',
// begin 12: Priceline hotels
'<a href="http://www.tkqlhce.com/click-988367-10987654" target="_blank"><img src="http://www.lduhtrp.net/image-988367-10987654" width=160 height=600 alt="" border=0></a>',
// begin 13: eCampus, sell your textbooks for cash! picture of an apple
'<a href="http://www.tkqlhce.com/click-988367-10569313" target="_blank"><img src="http://www.ftjcfx.com/image-988367-10569313" width=160 height=600 border=0></a>',
// begin 14: Travelocity, car rentals
'<a href="http://www.tkqlhce.com/click-988367-12104811-1432673639000" target="_blank"><img src="http://www.lduhtrp.net/image-988367-12104811-1432673639000" width="160" height="600" alt="" border="0"></a>',
// begin 15: NewEgg, Go green. eco-friendly deals
'<a href="http://www.tkqlhce.com/click-988367-10450961" target="_blank"><img src="http://www.awltovhc.com/image-988367-10450961" width=160 height=600 alt="" title=" Once You Know, You Newegg " border=0></a>',
// begin 16: Otterbox. added June 24, 2016
'<a href="http://www.tkqlhce.com/click-988367-12004004-1440024949000" target="_blank"><img src="http://www.ftjcfx.com/image-988367-12004004-1440024949000" width="160" height="600" alt="OtterBox.com: 160x600 Free Shipping" border="0"></a>',
// begin 16: HP // COMMENTED OUT JUNE 24, 2016. DEPARTED LINKSHARE AUG 1, 2016
//'<a href="http://click.linksynergy.com/fs-bin/click?id=2GqXwp1ktwQ&offerid=289612.392&subid=0&type=4" target="_blank"><IMG border="0" alt=" HP.com (Hewlett-Packard) " src="http://ad.linksynergy.com/fs-bin/show?id=2GqXwp1ktwQ&bids=289612.392&subid=0&type=4&gridnum=9"></a>',
// begin 17: Sharper Image, expires Aug 3, 2018. "Free shipping on any order of $50 or more
'<a href="http://click.linksynergy.com/fs-bin/click?id=2GqXwp1ktwQ&offerid=291398.10000899&subid=0&type=4" target="_blank"><IMG border="0" alt="" title=" Sharper Image " src="http://ad.linksynergy.com/fs-bin/show?id=2GqXwp1ktwQ&bids=291398.10000899&subid=0&type=4&gridnum=9"></a>',
// begin 18: KitchenAid. added June 24, 2016
'<a href="http://www.anrdoezrs.net/click-988367-11633407-1386366705000" target="_blank"><img src="http://www.ftjcfx.com/image-988367-11633407-1386366705000" width="160" height="600" alt="" border="0"/></a>',
// begin 19: Sharper Image, $15 off $150. expires Aug 3, 2018
'<a href="http://click.linksynergy.com/fs-bin/click?id=2GqXwp1ktwQ&offerid=291398.10000893&subid=0&type=4" target="_blank"><IMG border=0 alt="Sharper Image" src="http://ad.linksynergy.com/fs-bin/show?id=2GqXwp1ktwQ&bids=291398.10000893&subid=0&type=4&gridnum=9"></a>']
if (navigator.userAgent.indexOf('Android')>-1 || navigator.userAgent.indexOf('iPad')>-1 || navigator.userAgent.indexOf('iPhone')>-1) {nGoo[5]=nGoo[0];}
} // end if (s==0)
var iwid=Math.round(hyest*Math.random());
for (c0=3; c0<=adnum; c0++) {
if (iwid>hyest) {iwid=iwid-hyest-1;}
if (iwid<0) {iwid=0;}
adstr[c0-1]='<table border=0 cellspacing=0 cellpadding=0 style="width:'+String(tallwid[s]+tallmar)+'px; margin-bottom:'+String(adspacehite)+'px; margin-top:0px"><tr><td style="text-align:'+String(talllorr)+'; vertical-align:top">';
adstr[c0-1]+=String(nGoo[iwid])+'</td></tr></table>';
iwid+=c0+Math.round(4*Math.random()+1);
//if (c0==3) {iwid+=2;}
//if (c0>3) {iwid+=c0-2;}
} // end for c0
} // end if (adnum>2)
// end of non-google ad code


//begin adstring assembly
var adstring=adstr[0];
if (adnum>1) {
for (c0=1; c0<=adnum-1; c0++) {
adstring+=adstr[c0];
}
}
// pause adstring assembly

} // end if adnum>0

// begin exasin code, if exasin does not equal zero
if (exasin!=0) {
if (s==0) {
var exasinad='<table style="width:160px; height:280px; float:'+String(talllorr)+'" border=1 cellspacing=0 cellpadding=0><tr>';
}
if (s==1) {
var exasinad='<table style="width:120px; height:240px; float:'+String(talllorr)+'" border=0 cellspacing=0 cellpadding=0><tr>';
}
exasinad+='<td bgcolor="white" style="text-align:center; vertical-align:middle">';
// NEXT LINE ADDED DEC 10, 2016
exasinad+='<iframe name="extrabox" id="extrabox" style="width:120px;height:240px;" marginwidth="0" marginheight="0" scrolling="no" frameborder="0" src="//ws-na.amazon-adsystem.com/widgets/q?ServiceVersion=20070822&OneJS=1&Operation=GetAdHtml&MarketPlace=US&source=ac&ref=tf_til&ad_type=product_link&tracking_id=wavsourcecom-20&marketplace=amazon&region=US&placement='+String(exasin)+'&asins='+String(exasin)+'&linkId=92779e9ff932cc7d012574f265461d6e&show_border=true&link_opens_in_new_window=true&price_color=333333&title_color=0066c0&bg_color=ffffff"></iframe>'+
// NEXT LINE IS OLDER PRODUCT AD CODE -- DOESN'T WORK ANYMORE
//exasinad+='<iframe name="extrabox" id="extrabox" src="http://rcm-na.amazon-adsystem.com/e/cm?lt1=_blank&bc1=000000&IS2=1&bg1=FFFFFF&fc1=000000&lc1=0000FF&t=wavsourcecom-20&o=1&p=8&l=as1&m=amazon&f=ifr&asins='+String(exasin)+'" style="width:120px; height:240px" scrolling="no" marginwidth="0" marginheight="0" frameborder="0"></iframe>'+
'</td></tr></table>';
}
//end exasin code

// continue adstring assembly, if exasin does not equal zero
if (adnum>0 && exasin!=0) {adstring+=exasinad;}
if (adnum==0 && exasin!=0) {var adstring=exasinad;}
// end adstring assembly

// set adstring to nothing if there are no tall ads and no exasin
if (adnum==0 && exasin==0) {var adstring='';}

// begin display in left column, if left has been chosen
if (riteorleft==0) {
$(adstring).appendTo( $('#TTTL') );       // this line appends adstring onto the end of the pre-exising google ad in the left column
//$(adstring).insertBefore( $('#TTTL') ); // this line was replaced with the line above, after a google ad was drawn in left column prior to this js file being executed
}
// end display in left column
