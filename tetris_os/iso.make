TetOS.iso: TetOS.img
	cp TetOS.img images/iso/
	mkisofs -pad -b TetOS.img -R -o TetOS.iso images/iso/