#ifndef APP_DEF_H
#define APP_DEF_H

#define switch_cc_ret(aaa,bbb) if (cc->vurl.size()) {if (*cc->vurl.begin() == aaa) {cc->vurl.erase(cc->vurl.begin());bbb;return;}}
#define switch_cc(aaa,bbb) if (cc->vurl.size()) {if (*cc->vurl.begin() == aaa) {cc->vurl.erase(cc->vurl.begin());bbb;}}
#define switch_this_ret(aaa,bbb) if (vurl.size()) {if (*vurl.begin() == aaa) {vurl.erase(vurl.begin());bbb;return;}}
#define switch_this(aaa,bbb) if (vurl.size()) {if (*vurl.begin() == aaa) {vurl.erase(vurl.begin());bbb;}}
#define LICENSE_CK(aaa)
#endif
