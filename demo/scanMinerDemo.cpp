//
// echo_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "utils/OOLuaHelper.h"
#include "miner/MinerScanner.h"
#include "utils/IpGenerator.h"

using namespace std;
using namespace btctools::miner;
using namespace btctools::utils;

int main(int argc, char* argv[])
{
    try
    {
		OOLuaHelper::setPackagePath("./lua/scripts");

		btctools::utils::IpGenerator ips("192.168.200.0-192.168.201.255");
		auto ipRange = ips.genIpRange();
		MinerScanner scanner(ipRange, 100);

		auto source = scanner.run(1); // timeout: 1
		// fetch results
		for (auto miner : source)
		{
			cout << miner.ip_ << "\t" << miner.opt("a") << "\t" << miner.stat_ << "\t" << miner.typeStr_ << "\t" << miner.fullTypeStr_ << "\t" << miner.pool1_.url_ << "\t" << miner.pool1_.worker_ << endl;
		}
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
	catch (...)
	{
		cerr << "Unknown error!" << endl;
	}

    std::cout << "\nDone" << std::endl;

#ifdef _WIN32
	::system("pause");
#endif

    return 0;
}
