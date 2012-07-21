#!/bin/bash

echo "hello"
gst-launch -v udpsrc port=5006 caps="application/x-rtp, media=\(string\)video, clock-rate=\(int)90000, encoding-name=\(string\)JPEG, ssrc=\(guint\)469657143, payload=\(int\)96, clock-base=\(guint\)2841649723, seqnum-base=\(guint\)39869"   ! rtpjpegdepay ! jpegdec !  ffmpegcolorspace ! ximagesink
