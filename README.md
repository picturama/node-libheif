node-libheif
============

Native node bindings for [libheif](https://github.com/strukturag/libheif) - a HEIF image decoder.

There are JavaScript-only builds of `libheif` - like [libheif-js](https://www.npmjs.com/package/libheif-js) or
[heic2any](https://github.com/alexcorvi/heic2any).

The difference is:

  - `node-libheif` is about 3 x faster (1100 ms instead of 3300 ms for a 3024 x 4032 image).
  - `node-libheif` has native parts, so `node-libheif` will only work in a nodejs environment - it won't run in a browser.


Usage
-----

Install `node-libheif`:

    npm i --save node-libheif

Decode a image:

```javascript
import { loadHeifFromFile } from 'node-libheif'

const decodedImage = loadHeifFromFile('path/to/myimage.heic')
decodedImage.width   // Width in px
decodedImage.height  // Height in px
decodedImage.data    // Buffer with RGB data (8 bit per channel). size in bytes = 3 * width * height
```
