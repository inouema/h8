#ifndef _CONFIG_DEBUG_H_
#define _CONFIG_DEBUG_H_


#ifdef DEBUG
#define DPUTS( message )            puts( message )
#define DPUTXVAL( val, column )     putxval( val, column)
#else /* DEBUG */
#define DPUTS( message )
#define DPUTXVAL( val, column )
#endif /* DEBUG */

#endif /* _CONFIG_DEBUG_H_ */
