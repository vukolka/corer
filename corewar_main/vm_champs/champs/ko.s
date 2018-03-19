.name		"KOKOKO"
.comment	"Jour J"

		ld   65,r3		
		zjmp %0				# pour eviter ecrasement
						# de l'instruction suivante
code:		live %1			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %0			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %1			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %0			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		sti  r15,%0,r14			# 6
		zjmp %-200
