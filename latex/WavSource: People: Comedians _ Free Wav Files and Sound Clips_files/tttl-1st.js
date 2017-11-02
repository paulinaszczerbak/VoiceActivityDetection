var highest160=19;
var highest120=11;
var adhitefactor=600;
var tallwid = [160, 120];
//var s=Math.round(80*Math.random()); // commented-out July 8, 2015
var s=0; // added July 8, 2015, to make all tall ads 160 pixels wide. if 120-pixel ads are added back, nGoo variable must be accounted for (below).
var s3;
if (riteorleft==1) {
talllorr='right';
} else {
talllorr='left';
}
var exasin;
if (!exasin || exasin=='undefined' || exasin=='') {exasin=0;}

if (riteorleft==0) {
document.write('<table border=0 cellspacing=0 cellpadding=0 style="width:',tallwid[s]+tallmar,'px; margin-bottom:',adspacehite,'px; margin-top:0px"><tr><td style="text-align:',talllorr,'; vertical-align:top">',
'<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"><\/script>',
'<ins class="adsbygoogle"',
'     style="display:inline-block;width:',tallwid[s],'px;height:600px"',
'     data-ad-client="ca-pub-0780163802383173"');
if (riteorleft==0 && s==0) {document.write('     data-ad-slot="2774662235"></ins>');} // 160 left image
if (riteorleft==1 && s==0) {document.write('     data-ad-slot="8681595038"></ins>');} // 160 right image
if (riteorleft==0 && s==1) {document.write('     data-ad-slot="4111794635"></ins>');} // 120 left image
if (riteorleft==1 && s==1) {document.write('     data-ad-slot="5448927033"></ins>');} // 120 right image
document.write('<script>(adsbygoogle = window.adsbygoogle || []).push(\{\})\;<\/script></td></tr></table>');
} else {
document.write('<table border=0 cellspacing=0 cellpadding=0 style="width:',tallwid[s],'px; height:1px"></table>');
}
