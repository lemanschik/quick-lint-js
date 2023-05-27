# code-oss-web
Many people are aware of vscode it started as backend file manager for azure cloud and did become vscode.
THe Open Source version is called code-oss and the web build is called code-oss-web.

This implements the cloud-fs.zip Workspace Extension and uses it as quick-lint workspace that bypasses the LSP implementation
as this has no such LSP Implementation as this is a Workspace Implementation

## Usage 
Copy the content of this folder directly to your web server run npm install or yarn before in that folder.

## Build
https://github.com/lemanschik/quick-lint-js/blob/ide/website/wasm/README.md


## Demo
```
https://quick-lint-js.com/demo/demo.bundled.js
https://quick-lint-js.com/demo/dist/quick-lint-js-vscode.wasm
```

## Why? 
The Author of Quic Lint is known to be not the most clever while he is able to implement some fundamental algos
and manual write and debug code he is not able to studie tie interfaces that he uses so we created a fork that solves that
this is 10x faster then quick lint is normal in code-oss

He was thinking that he needs to use the LSP but thats wrong he needs to use the workspace api the LSP is connected to the workspace
FileSystemProvider and textSearchProvider 

```html
<!DOCTYPE html>
<!-- Copyright (C) 2020  Matthew "strager" Glazar -->
<!-- See end of file for extended copyright information. -->
<html>
  <head>
    

<meta charset="utf-8" />
<meta content="width=device-width, initial-scale=1" name="viewport" />
<link
  rel="icon"
  type="image/png"
  sizes="16x16"
  href="../favicon-16x16.png"
/>
<link
  rel="icon"
  type="image/png"
  sizes="32x32"
  href="../favicon-32x32.png"
/>
<link rel="canonical" href="https://quick-lint-js.com/demo/" />
<meta property="og:url" content="https://quick-lint-js.com/demo/" />

<title>Try quick-lint-js in your browser</title>
<meta
  property="og:title"
  content="Try quick-lint-js in your browser"
/>
 
<meta
  property="og:image"
  content="/vscode-demo-small.gif"
/>
<meta name="theme-color" content="#a76851" />
<meta property="og:type" content="website" />
<meta name="twitter:card" content="summary_large_image" />


    <link href="../main.css" rel="stylesheet" />
    <style>
      /* Make #code-input and #shadow-code-input have the same size. */
      main {
        position: relative;
      }
      .code-view {
        width: 100%;
        height: 20em;
      }

      /* Normalize #code-input, #code-input-marks-scroller, and
         #shadow-code-input to have the internal layout. */
      .code-view {
        border: 0;
        box-sizing: border-box;
        font-family: monospace;
        font-size: 1rem;
        line-height: 1em;
        margin: 0;
        overflow: scroll;
        padding: 3px;
        white-space: pre;
      }

      #code-input-marks {
        margin: 0;
        padding: 0;
      }

      /* Show #code-input-marks-scroller visually behind #code-input. */
      #code-input {
        background: transparent;
        position: relative;
        z-index: 2;
        outline: none;
      }
      #code-input-marks-scroller {
        color: transparent;
        z-index: 1;
        /* !important is required because codegrepper extension adds position:relative
        the html tag and breaks the demo */
        position: absolute !important;
        padding: 0;
      }

      /* Hide #shadow-code-input, but ensure its layout is accessible from
         JavaScript. */
      #shadow-code-input {
        /* !important is required because codegrepper extension adds position:relative
        the html tag and breaks the demo */
        position: absolute !important;
        visibility: hidden;
      }

      /* Don't show duplicate scroll bars. */
      #code-input-marks-scroller {
        overflow: hidden;
      }

      #code-input-marks-scroller {
        background-color: rgba(0, 0, 0, 0.05);
      }

      .floating-mark {
        position: absolute;
      }

      footer {
        border-top: 0;
      }

      @media (prefers-color-scheme: dark) {
        #code-input {
          color: white;
        }

        #code-input-marks-scroller {
          background-color: rgba(0, 0, 0, 0.2);
        }
      }
    </style>
  </head>
  <body class="side-bar-nav">
    <!--
    Known bugs:

    * Empty marks (indicating missing semicolons) are practically invisible
      on Chrome due to its thick underline.
    * Overscrolling on macOS has visual issues.
    * Scrolling in general works poorly when sub-pixel scrolling (e.g. when
      zoomed in).
    * Scrolling horizontally sometimes doesn't scroll the highlights.
    * Browser text search finds text in the shadow code input in addition to
      text in the user code input.

    -->

    <header>

<script>
  //
</script>


<h1><a href="../">quick-lint-js</a></h1>

<p class="tag-line">Find bugs in JavaScript programs.</p>
<a
  href="../"
  class="mascot"
  ><img
    class="mascot"
    src="../dusty.svg"
    title="Dusty, the quick-lint-js mascot"
    alt=""
    width="111"
    height="86"
  /></a
>

<nav class="main-nav">
  <ul>
    
    <li class="side-bar-only">
      <a href="../">Home</a>
    </li>
      
    <li class="">
          <a href="../install/">Install</a>
          </li> 
      <li class=" side-bar-only"><span class="current-page">Try online</span></li> 
     
    <li class="">
          <a href="../docs/">Docs</a>
          </li> 
      <li class="">
          <a href="../benchmarks/">Benchmarks</a>
        </li> 
     
    <li class="">
          <a href="../contribute/">Contribute</a>
          </li> 
     
    <li class="">
          <a href="../blog/">Blog</a>
          </li> 
    
  </ul>
</nav>


</header>

    <main>
      <h2>Demo</h2>

      <p>
        See how quick-lint-js works right here in your browser! Paste your
        favorite buggy JavaScript code below:
      </p>

      <pre class="code-view" id="shadow-code-input"></pre>
      <pre
        class="code-view"
        id="code-input-marks-scroller"
      ><pre id="code-input-marks"></pre></pre>
      <textarea class="code-view" id="code-input" spellcheck="false">
const occupation = language + " coder";
const language = "JavaScript";
occupation = "Senior " + occupation;

console.log(`Welcome, ${ocupation}!`);
</textarea
      >

      <script src="demo.bundled.js"></script>
    </main>

    <footer>

<script>
  //
</script>

<nav>
  <ul>
      <li>
      <a href="../"
        >quick-lint-js home page</a
      >
    </li>      <li>
      <a href="../hiring/"
        >we&#39;re hiring! get paid to code</a
      >
    </li>    <li>
      <a href="../merch/"
        >buy quick-lint-js merch</a
      >
    </li>    <li>
      <a href="../benchmarks/"
        >benchmarks vs other linters</a
      >
    </li>    <li>
      <a href="https://github.com/quick-lint/quick-lint-js"
        >source code on GitHub</a
      >
    </li>    <li>
      <a href="../license/"
        >copyright and license information</a
      >
    </li>  
  </ul>
</nav>


</footer>
  </body>
</html>

<!--
quick-lint-js finds bugs in JavaScript programs.
Copyright (C) 2020  Matthew "strager" Glazar

This file is part of quick-lint-js.

quick-lint-js is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

quick-lint-js is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
-->
```
