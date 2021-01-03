
var b;
b || (b = typeof Module !== 'undefined' ? Module : {});
var h = {}, k;
for (k in b) {
  b.hasOwnProperty(k) && (h[k] = b[k]);
}
function m(a, c) {
  throw c;
}
var n = !1, p = !1, q = !1, aa = !1;
n = "object" === typeof window;
p = "function" === typeof importScripts;
q = "object" === typeof process && "object" === typeof process.versions && "string" === typeof process.versions.node;
aa = !n && !q && !p;
var r = "", t, u, v, w;
if (q) {
  r = p ? require("path").dirname(r) + "/" : __dirname + "/", t = function(a, c) {
    v || (v = require("fs"));
    w || (w = require("path"));
    a = w.normalize(a);
    return v.readFileSync(a, c ? null : "utf8");
  }, u = function(a) {
    a = t(a, !0);
    a.buffer || (a = new Uint8Array(a));
    a.buffer || x("Assertion failed: undefined");
    return a;
  }, 1 < process.argv.length && process.argv[1].replace(/\\/g, "/"), process.argv.slice(2), "undefined" !== typeof module && (module.exports = b), process.on("uncaughtException", function(a) {
    if (!(a instanceof y)) {
      throw a;
    }
  }), process.on("unhandledRejection", x), m = function(a) {
    process.exit(a);
  }, b.inspect = function() {
    return "[Emscripten Module object]";
  };
} else {
  if (aa) {
    "undefined" != typeof read && (t = function(a) {
      return read(a);
    }), u = function(a) {
      if ("function" === typeof readbuffer) {
        return new Uint8Array(readbuffer(a));
      }
      a = read(a, "binary");
      "object" === typeof a || x("Assertion failed: undefined");
      return a;
    }, "function" === typeof quit && (m = function(a) {
      quit(a);
    }), "undefined" !== typeof print && ("undefined" === typeof console && (console = {}), console.log = print, console.warn = console.error = "undefined" !== typeof printErr ? printErr : print);
  } else {
    if (n || p) {
      p ? r = self.location.href : document.currentScript && (r = document.currentScript.src), r = 0 !== r.indexOf("blob:") ? r.substr(0, r.lastIndexOf("/") + 1) : "", t = function(a) {
        var c = new XMLHttpRequest;
        c.open("GET", a, !1);
        c.send(null);
        return c.responseText;
      }, p && (u = function(a) {
        var c = new XMLHttpRequest;
        c.open("GET", a, !1);
        c.responseType = "arraybuffer";
        c.send(null);
        return new Uint8Array(c.response);
      });
    }
  }
}
var ba = b.print || console.log.bind(console), z = b.printErr || console.warn.bind(console);
for (k in h) {
  h.hasOwnProperty(k) && (b[k] = h[k]);
}
h = null;
b.quit && (m = b.quit);
var A;
b.wasmBinary && (A = b.wasmBinary);
var noExitRuntime;
b.noExitRuntime && (noExitRuntime = b.noExitRuntime);
"object" !== typeof WebAssembly && z("no native wasm support detected");
var B, fa = new WebAssembly.Table({initial:7, maximum:7, element:"anyfunc"}), C = !1, ha = "undefined" !== typeof TextDecoder ? new TextDecoder("utf8") : void 0;
function ia(a, c, d) {
  var e = c + d;
  for (d = c; a[d] && !(d >= e);) {
    ++d;
  }
  if (16 < d - c && a.subarray && ha) {
    return ha.decode(a.subarray(c, d));
  }
  for (e = ""; c < d;) {
    var f = a[c++];
    if (f & 128) {
      var g = a[c++] & 63;
      if (192 == (f & 224)) {
        e += String.fromCharCode((f & 31) << 6 | g);
      } else {
        var l = a[c++] & 63;
        f = 224 == (f & 240) ? (f & 15) << 12 | g << 6 | l : (f & 7) << 18 | g << 12 | l << 6 | a[c++] & 63;
        65536 > f ? e += String.fromCharCode(f) : (f -= 65536, e += String.fromCharCode(55296 | f >> 10, 56320 | f & 1023));
      }
    } else {
      e += String.fromCharCode(f);
    }
  }
  return e;
}
"undefined" !== typeof TextDecoder && new TextDecoder("utf-16le");
var D, E, F, G, H, I, J = b.INITIAL_MEMORY || 16777216;
b.wasmMemory ? B = b.wasmMemory : B = new WebAssembly.Memory({initial:J / 65536, maximum:J / 65536});
B && (D = B.buffer);
J = D.byteLength;
var K = D;
D = K;
b.HEAP8 = E = new Int8Array(K);
b.HEAP16 = G = new Int16Array(K);
b.HEAP32 = H = new Int32Array(K);
b.HEAPU8 = F = new Uint8Array(K);
b.HEAPU16 = new Uint16Array(K);
b.HEAPU32 = new Uint32Array(K);
b.HEAPF32 = new Float32Array(K);
b.HEAPF64 = I = new Float64Array(K);
H[1640] = 5249600;
function L(a) {
  for (; 0 < a.length;) {
    var c = a.shift();
    if ("function" == typeof c) {
      c(b);
    } else {
      var d = c.l;
      "number" === typeof d ? void 0 === c.b ? b.dynCall_v(d) : b.dynCall_vi(d, c.b) : d(void 0 === c.b ? null : c.b);
    }
  }
}
var ja = [], ka = [], la = [], ma = [], na = [];
function oa() {
  var a = b.preRun.shift();
  ja.unshift(a);
}
var M = 0, N = null, O = null;
b.preloadedImages = {};
b.preloadedAudios = {};
function x(a) {
  if (b.onAbort) {
    b.onAbort(a);
  }
  ba(a);
  z(a);
  C = !0;
  throw new WebAssembly.RuntimeError("abort(" + a + "). Build with -s ASSERTIONS=1 for more info.");
}
function P(a) {
  var c = Q;
  return String.prototype.startsWith ? c.startsWith(a) : 0 === c.indexOf(a);
}
function pa() {
  return P("data:application/octet-stream;base64,");
}
var Q = "tmouse.wasm";
if (!pa()) {
  var qa = Q;
  Q = b.locateFile ? b.locateFile(qa, r) : r + qa;
}
function ra() {
  try {
    if (A) {
      return new Uint8Array(A);
    }
    if (u) {
      return u(Q);
    }
    throw "both async and sync fetching of the wasm failed";
  } catch (a) {
    x(a);
  }
}
function sa() {
  return A || !n && !p || "function" !== typeof fetch || P("file://") ? new Promise(function(a) {
    a(ra());
  }) : fetch(Q, {credentials:"same-origin"}).then(function(a) {
    if (!a.ok) {
      throw "failed to load wasm binary file at '" + Q + "'";
    }
    return a.arrayBuffer();
  }).catch(function() {
    return ra();
  });
}
var ta = {1578:function() {
  b.canvas.style.backgroundColor = "black";
}, 1838:function() {
  var a = {screenX:123, screenY:456, clientX:123, clientY:456, button:0, buttons:1}, c = document.createEvent("Event");
  c.initEvent("click", !0, !0);
  for (var d in a) {
    c[d] = a[d];
  }
  window.dispatchEvent(c);
}, 2150:function() {
  function a(c, d) {
    var e = document.createEvent("Event");
    e.initEvent(c, !0, !0);
    for (var f in d) {
      e[f] = d[f];
    }
    window.dispatchEvent(e);
  }
  a("click", {screenX:-5E5, screenY:-5E5, clientX:-5E5, clientY:-5E5, button:0, buttons:0});
  a("mousedown", {screenX:1, screenY:1, clientX:1, clientY:1, button:0, buttons:1});
  a("mouseup", {screenX:1, screenY:1, clientX:1, clientY:1, button:0, buttons:0});
  a("dblclick", {screenX:1, screenY:1, clientX:1, clientY:1, button:0, buttons:0});
  a("mousemove", {screenX:1, screenY:1, clientX:1, clientY:1, button:0, buttons:0, movementX:1, movementY:1});
  a("wheel", {screenX:1, screenY:1, clientX:1, clientY:1, button:0, buttons:0, deltaX:1, deltaY:1, deltaZ:1, deltaMode:1});
  a("mousewheel", {screenX:1, screenY:1, clientX:1, clientY:1, button:0, buttons:0, wheelDeltaX:1, wheelDeltaY:1});
}, 3161:function() {
  b.noExitRuntime = !0;
}};
ka.push({l:function() {
  ua();
}});
function va() {
  for (var a = R.length - 1; 0 <= a; --a) {
    wa(a);
  }
  R = [];
  S = [];
}
var S = [];
function xa() {
  if (T.i && ya.f) {
    for (var a = 0; a < S.length; ++a) {
      var c = S[a];
      S.splice(a, 1);
      --a;
      c.o.apply(null, c.m);
    }
  }
}
var R = [];
function wa(a) {
  var c = R[a];
  c.target.removeEventListener(c.a, c.j, c.c);
  R.splice(a, 1);
}
function Aa(a) {
  function c(e) {
    ++T.i;
    ya = a;
    xa();
    a.h(e);
    xa();
    --T.i;
  }
  if (a.g) {
    a.j = c, a.target.addEventListener(a.a, c, a.c), R.push(a), Ba || (ma.push(va), Ba = !0);
  } else {
    for (var d = 0; d < R.length; ++d) {
      R[d].target == a.target && R[d].a == a.a && wa(d--);
    }
  }
}
var T = {}, Ba, ya, U, V, Ca = [0, "undefined" !== typeof document ? document : 0, "undefined" !== typeof window ? window : 0];
function W(a) {
  a = 2 < a ? a ? ia(F, a, void 0) : "" : a;
  return Ca[a] || ("undefined" !== typeof document ? document.querySelector(a) : void 0);
}
function Da(a, c, d) {
  a >>= 2;
  H[a] = c.screenX;
  H[a + 1] = c.screenY;
  H[a + 2] = c.clientX;
  H[a + 3] = c.clientY;
  H[a + 4] = c.ctrlKey;
  H[a + 5] = c.shiftKey;
  H[a + 6] = c.altKey;
  H[a + 7] = c.metaKey;
  G[2 * a + 16] = c.button;
  G[2 * a + 17] = c.buttons;
  H[a + 9] = c.movementX;
  H[a + 10] = c.movementY;
  d = 0 > Ca.indexOf(d) ? d.getBoundingClientRect() : {left:0, top:0};
  H[a + 11] = c.clientX - d.left;
  H[a + 12] = c.clientY - d.top;
}
function X(a, c, d, e, f, g) {
  U || (U = Y(64));
  a = W(a);
  Aa({target:a, f:"mousemove" != g && "mouseenter" != g && "mouseleave" != g, a:g, g:e, h:function(l) {
    l = l || event;
    Da(U, l, a);
    Ea(e, f, U, c) && l.preventDefault();
  }, c:d});
}
function Fa(a, c, d, e) {
  V || (V = Y(96));
  Aa({target:a, f:!0, a:"wheel", g:e, h:function(f) {
    f = f || event;
    var g = V;
    Da(g, f, a);
    I[g + 64 >> 3] = f.deltaX;
    I[g + 72 >> 3] = f.deltaY;
    I[g + 80 >> 3] = f.deltaZ;
    H[g + 88 >> 2] = f.deltaMode;
    Ea(e, 9, g, c) && f.preventDefault();
  }, c:d});
}
var Ga = [null, [], []], Ha = [], Ia = {emscripten_asm_const_iii:function(a, c, d) {
  Ha.length = 0;
  var e;
  for (d >>= 2; e = F[c++];) {
    Ha.push(105 > e ? I[++d >> 1] : H[d]), ++d;
  }
  return ta[a].apply(null, Ha);
}, emscripten_get_mouse_status:function(a) {
  if (!U) {
    return -7;
  }
  E.set(E.subarray(U, U + 64), a);
  return 0;
}, emscripten_get_sbrk_ptr:function() {
  return 6560;
}, emscripten_memcpy_big:function(a, c, d) {
  F.copyWithin(a, c, c + d);
}, emscripten_resize_heap:function() {
  x("OOM");
}, emscripten_set_canvas_element_size:function(a, c, d) {
  a = W(a);
  if (!a) {
    return -4;
  }
  a.width = c;
  a.height = d;
  return 0;
}, emscripten_set_click_callback_on_thread:function(a, c, d, e) {
  X(a, c, d, e, 4, "click");
  return 0;
}, emscripten_set_dblclick_callback_on_thread:function(a, c, d, e) {
  X(a, c, d, e, 7, "dblclick");
  return 0;
}, emscripten_set_mousedown_callback_on_thread:function(a, c, d, e) {
  X(a, c, d, e, 5, "mousedown");
  return 0;
}, emscripten_set_mousemove_callback_on_thread:function(a, c, d, e) {
  X(a, c, d, e, 8, "mousemove");
  return 0;
}, emscripten_set_mouseup_callback_on_thread:function(a, c, d, e) {
  X(a, c, d, e, 6, "mouseup");
  return 0;
}, emscripten_set_wheel_callback_on_thread:function(a, c, d, e) {
  a = W(a);
  return "undefined" !== typeof a.onwheel ? (Fa(a, c, d, e), 0) : -1;
}, fd_write:function(a, c, d, e) {
  for (var f = 0, g = 0; g < d; g++) {
    for (var l = H[c + 8 * g >> 2], za = H[c + (8 * g + 4) >> 2], ca = 0; ca < za; ca++) {
      var da = F[l + ca], ea = Ga[a];
      0 === da || 10 === da ? ((1 === a ? ba : z)(ia(ea, 0)), ea.length = 0) : ea.push(da);
    }
    f += za;
  }
  H[e >> 2] = f;
  return 0;
}, memory:B, setTempRet0:function() {
}, table:fa};
(function() {
  function a(f) {
    b.asm = f.exports;
    M--;
    b.monitorRunDependencies && b.monitorRunDependencies(M);
    0 == M && (null !== N && (clearInterval(N), N = null), O && (f = O, O = null, f()));
  }
  function c(f) {
    a(f.instance);
  }
  function d(f) {
    return sa().then(function(g) {
      return WebAssembly.instantiate(g, e);
    }).then(f, function(g) {
      z("failed to asynchronously prepare wasm: " + g);
      x(g);
    });
  }
  var e = {env:Ia, wasi_snapshot_preview1:Ia};
  M++;
  b.monitorRunDependencies && b.monitorRunDependencies(M);
  if (b.instantiateWasm) {
    try {
      return b.instantiateWasm(e, a);
    } catch (f) {
      return z("Module.instantiateWasm callback failed with error: " + f), !1;
    }
  }
  (function() {
    if (A || "function" !== typeof WebAssembly.instantiateStreaming || pa() || P("file://") || "function" !== typeof fetch) {
      return d(c);
    }
    fetch(Q, {credentials:"same-origin"}).then(function(f) {
      return WebAssembly.instantiateStreaming(f, e).then(c, function(g) {
        z("wasm streaming compile failed: " + g);
        z("falling back to ArrayBuffer instantiation");
        return d(c);
      });
    });
  })();
  return {};
})();
var ua = b.___wasm_call_ctors = function() {
  return (ua = b.___wasm_call_ctors = b.asm.__wasm_call_ctors).apply(null, arguments);
};
b._main = function() {
  return (b._main = b.asm.main).apply(null, arguments);
};
b.___errno_location = function() {
  return (b.___errno_location = b.asm.__errno_location).apply(null, arguments);
};
b.stackSave = function() {
  return (b.stackSave = b.asm.stackSave).apply(null, arguments);
};
b.stackRestore = function() {
  return (b.stackRestore = b.asm.stackRestore).apply(null, arguments);
};
b.stackAlloc = function() {
  return (b.stackAlloc = b.asm.stackAlloc).apply(null, arguments);
};
var Y = b._malloc = function() {
  return (Y = b._malloc = b.asm.malloc).apply(null, arguments);
};
b._free = function() {
  return (b._free = b.asm.free).apply(null, arguments);
};
b.__growWasmMemory = function() {
  return (b.__growWasmMemory = b.asm.__growWasmMemory).apply(null, arguments);
};
var Ea = b.dynCall_iiii = function() {
  return (Ea = b.dynCall_iiii = b.asm.dynCall_iiii).apply(null, arguments);
};
b.dynCall_ii = function() {
  return (b.dynCall_ii = b.asm.dynCall_ii).apply(null, arguments);
};
b.dynCall_jiji = function() {
  return (b.dynCall_jiji = b.asm.dynCall_jiji).apply(null, arguments);
};
b.dynCall_iidiiii = function() {
  return (b.dynCall_iidiiii = b.asm.dynCall_iidiiii).apply(null, arguments);
};
var Z;
function y(a) {
  this.name = "ExitStatus";
  this.message = "Program terminated with exit(" + a + ")";
  this.status = a;
}
O = function Ja() {
  Z || Ka();
  Z || (O = Ja);
};
function Ka() {
  function a() {
    if (!Z && (Z = !0, b.calledRun = !0, !C)) {
      L(ka);
      L(la);
      if (b.onRuntimeInitialized) {
        b.onRuntimeInitialized();
      }
      if (La) {
        var c = b._main;
        try {
          var d = c(0, 0);
          if (!noExitRuntime || 0 !== d) {
            if (!noExitRuntime && (C = !0, b.onExit)) {
              b.onExit(d);
            }
            m(d, new y(d));
          }
        } catch (e) {
          e instanceof y || ("unwind" == e ? noExitRuntime = !0 : ((c = e) && "object" === typeof e && e.stack && (c = [e, e.stack]), z("exception thrown: " + c), m(1, e)));
        } finally {
        }
      }
      if (b.postRun) {
        for ("function" == typeof b.postRun && (b.postRun = [b.postRun]); b.postRun.length;) {
          c = b.postRun.shift(), na.unshift(c);
        }
      }
      L(na);
    }
  }
  if (!(0 < M)) {
    if (b.preRun) {
      for ("function" == typeof b.preRun && (b.preRun = [b.preRun]); b.preRun.length;) {
        oa();
      }
    }
    L(ja);
    0 < M || (b.setStatus ? (b.setStatus("Running..."), setTimeout(function() {
      setTimeout(function() {
        b.setStatus("");
      }, 1);
      a();
    }, 1)) : a());
  }
}
b.run = Ka;
if (b.preInit) {
  for ("function" == typeof b.preInit && (b.preInit = [b.preInit]); 0 < b.preInit.length;) {
    b.preInit.pop()();
  }
}
var La = !0;
b.noInitialRun && (La = !1);
noExitRuntime = !0;
Ka();

