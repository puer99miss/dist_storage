rpc_rootdir = ${top_srcdir}/src/rpc
top_dir=../../..
third_dir=${top_dir}/third-64
pub_dir=${top_dir}/pub_util

AM_CPPFLAGS=-I$(top_srcdir)/src \
            -I${third_dir}/protobuf/include/ \
			-I${third_dir}/libev/include/ \
			-I${third_dir}/boost/include/ \
			-I${third_dir}/glog/include/ \
			-I${pub_dir} 
			

AM_LDFLAGS=-lz -lrt

LDADD=${third_dir}/protobuf/lib/*.a \
	  ${third_dir}/libev/lib/*.a \
	  ${third_dir}/boost/lib/*.a \
	  ${third_dir}/glog/lib/*.a \
	  $(top_builddir)/src/common/libcommon.a


RPC_SRC=${rpc_rootdir}/rpc_server.h \
		${rpc_rootdir}/rpc_server.cpp \
		${rpc_rootdir}/libev_connector.h \
		${rpc_rootdir}/libev_connector.cpp \
		${rpc_rootdir}/io_thread.h \
		${rpc_rootdir}/io_thread.cpp \
		${rpc_rootdir}/thread_pool.h \
		${rpc_rootdir}/thread_pool.cpp \
		${rpc_rootdir}/rpc_channel.h \
		${rpc_rootdir}/rpc_channel.cpp \
		${rpc_rootdir}/rpc_util.h \
		${rpc_rootdir}/rpc_util.cpp \
		${rpc_rootdir}/socket_util.h \
		${rpc_rootdir}/socket_util.cpp \
		${rpc_rootdir}/rpc_msg.pb.h \
		${rpc_rootdir}/rpc_msg.pb.cc


noinst_LIBRARIES=librpc.a

librpc_a_SOURCES=${RPC_SRC}
