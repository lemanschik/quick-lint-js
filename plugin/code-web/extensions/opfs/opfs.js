// is loadable as service worker does not reload the page but activates instant
// you open opfs.html in a iframe with correct cors and security policys then
// it loads this file twice one time in the render process one time in a worker process
// then a 3rd time optional as shared worker for the whole scope only needed on large systems.
// allows scaling to infinity.
