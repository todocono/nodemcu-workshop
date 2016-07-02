const char page_style[] PROGMEM = R"=====(
* {margin: 0;padding: 0;box-sizing: border-box;}
body{font:12px/14px Arial, Verdana, helvetica, sans-serif;letter-spacing:.05em;}
p, form, h1{border:0; margin:0; padding:0;}
h1 {float:left;width:100%;font-size:1.4em;font-weight:bold;background:#f9f9f9;border:1px solid #ddd;padding: .8em 1em;margin:0 0 .5em 0;}
h2 {float:left;width:100%;font-size:1.1em;font-weight:bold;border-bottom:1px solid #e7e7e7;padding: 1em;margin:0 0 1em 0;}
form > div {clear: both;overflow: hidden;padding: .8em 0 .4em 0;margin: 0 0 .4em 0;border-bottom:1px solid #f5f5f5;}
form > div > label {float: left;width: 25%;padding: 2px 10px 0 0;text-align: right;}
form > div > label > span{float: left;width: 100%;font-size:11px;color:#aaa;}
form > div > div {float: right;width: 75%;margin: 0 0 .5em 0;}
input[type=text],input[type=email],input[type=url],input[type=password],textarea {width: 80%;padding:.4em .8em;border:1px solid #999;color:#999;}
input:focus,textarea:focus {border:1px solid #007095;color:#000;}
input[type=submit]{clear:both;width:40%;margin:1% 30% auto;padding:.3em 0;background:#008cba;border:1px solid #008cba;color:#fff;font-size: 1.1em;text-transform:uppercase;cursor: pointer;}
input[type=submit]:hover{background:#007095;}

.button-link {    padding: 10px 15px;    background: #4479BA;    color: #FFF;}
.toggle {position: absolute;margin-left: -9999px;visibility: hidden;}
.toggle + label {display: block;position: relative;cursor: pointer;outline: none;user-select: none;}
input.ios + label {padding: 2px;width: 40px;height: 20px;background-color: #dddddd;border-radius: 20px;}
input.ios + label:before,input.ios + label:after {display: block;position: absolute;top: 1px;left: 1px;bottom: 1px;content: "";}
input.ios + label:before {right: 1px;background-color: #df6969;border-radius: 22px;transition: background 0.4s;}
input.ios + label:after {width: 18px;background-color: #fff;border-radius: 100%;box-shadow: 0 1px 1px rgba(0, 0, 0, 0.3);transition: margin 0.4s;}
input.ios:checked + label:before {background-color: #63d771;}
input.ios:checked + label:after {margin-left: 20px;}

.top {width:100%;background:#555;color:#fff;}
.main {margin: 0 auto;max-width: 50rem;}.main:after {content: "";display: table;clear: both;}
.maint {margin-top:1.5rem;margin-bottom:2rem;}
.left {float: left;width: 20%;}.right {float: left;width: 80%;padding: 0 0 0 2em;}
.menu ul {list-style-type: none;margin: 0;padding: 2em 0 0;border-right:solid 1px #008cba;min-height:20rem;}
.menu li a {display: block;color: #555;text-align: left;padding: .8em 1em;margin: 0;text-decoration: none;}
.menu li a:hover {color:#008cba;}
.menu li a.active {color:#333;border:1px solid #008cba;border-right:solid 1px #fff;margin-right:-1px;}
.tmenu {padding: 0; margin: 0;}
.tmenu .logo {float:left;margin-top:1px;width: 80px;height: 35px;background: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADIAAAAjCAYAAADWtVmPAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENTNiAoV2luZG93cykiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6QzRDMjhFN0UxOERDMTFFNjk2OUJCNjk0NTA2NjAyM0EiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6QzRDMjhFN0YxOERDMTFFNjk2OUJCNjk0NTA2NjAyM0EiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDpDNEMyOEU3QzE4REMxMUU2OTY5QkI2OTQ1MDY2MDIzQSIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDpDNEMyOEU3RDE4REMxMUU2OTY5QkI2OTQ1MDY2MDIzQSIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PiWDR94AAAdpSURBVHja1FkJbFRF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) no-repeat center top;}
.tmenu ul {list-style-type: none;text-align: right; }
.tmenu li {display: inline-block;}
.tmenu li a {float:left;display: inline-block;color: #ccc;padding: 1em 2em;margin: 0;text-decoration: none;}
.tmenu li a:hover, .tmenu li a.active {background-color: #008cba;color:#fff;}
.gmenu{float:left;width:100%;padding: 0; margin: 0;}
.gmenu div {padding: 0; margin: 0;float:right;width:12%;}
.gmenu span {padding: 0; margin: 1em 0;float:left;width:50%;font-weight:600;}
.gmenu div div {padding: 0; margin: .75em 0;float:left;width:50%;}
.network ul {list-style-type: none;margin: 0;padding: 0;overflow: hidden;background:#f9f9f9;border:1px solid #ddd;}
.network li a {display: block;color: #666;text-align: left;padding: .5em 1em;text-decoration: none;}
.network li a:hover {background-color: #ccc;color:#008cba;}

@media (max-width: 50rem) {.left,.right {width: 96%;margin:0 2%;padding:0}.menu ul {padding: 0;border-right:0;border-bottom:solid 1px #008cba;min-height:2.50rem;}.menu li {float: left;}.menu li a {padding: 1em 2em;margin: 0 .3em 2em .3em;}.menu li a.active {border:1px solid #008cba;border-bottom:solid 1px #fff;}.main {margin-top:0;}button{margin:1% 35% auto;}.gmenu div {padding: 0; margin: 0;width:17%;margin-right:1em;}}
@media (max-width: 30rem) {.menu ul {min-height:2.5rem;}.menu li a {padding: .5em .8em;margin: 1em .1em;}.gmenu div {width:30%;}}

)=====";
 
