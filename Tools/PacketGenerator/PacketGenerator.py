import argparse
import jinja2
import ProtoParser

def main():

	arg_parser = argparse.ArgumentParser(description = 'PacketGenerator')
	arg_parser.add_argument('--path', type=str, default='C:/Neta500/Project1/Protobuf/Protocol.proto', help='proto path')
	args = arg_parser.parse_args()

	parser = ProtoParser.ProtoParser(1000, 'C_', 'S_')
	parser.parse_proto(args.path)
	file_loader = jinja2.FileSystemLoader('../Tools/PacketGenerator/Templates')
	env = jinja2.Environment(loader=file_loader)

	# ClientPacketHandler
	template = env.get_template('ClientPacketHandler.txt')
	output = template.render(parser=parser, output='ClientPacketHandler.h')

	# ProtocolEnum.h
	template_enum = env.get_template('PDL.txt')
	output_enum = template_enum.render(parser=parser, output='PDL.h')

	# ProtocolEnum.cs
	template_enum_dummyclient = env.get_template('PDL_DummyClient.txt')
	output_enum_dummyclient = template_enum_dummyclient.render(parser=parser, output='PDL_DummyClient.cs')

	f = open('ClientPacketHandler.h', 'w+')
	f.write(output)
	f.close()

	f_enum = open('PDL.h', 'w+')
	f_enum.write(output_enum)
	f_enum.close()

	f_enum_dc = open('PDL_DummyClient.cs', 'w+')
	f_enum_dc.write(output_enum_dummyclient)
	f_enum_dc.close()

	#print(output)
	
	return

if __name__ == '__main__':
	main()