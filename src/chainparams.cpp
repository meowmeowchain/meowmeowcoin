// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include <stdio.h>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  1000, uint256("0x0000e9eb75716cfc975362d7b6fd8419a3c17d752f1ec56845684be914160d8b"))
	(  2000, uint256("0x0000a9c49a80346e0a5ab1c07ffadde9f8c42a8e1f54776927ea3a6843a02397"))
	(  5000, uint256("0x00000086c7befa4e7b1a92521f8a227aaec836a914b30f530cf0bb580bd6ead4"))
	( 10000, uint256("0x00000005926ee15ca857825b86cf638ecc7bedf3ff62b5eaab39911627a8e451"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1518612461, // * UNIX timestamp of last checkpoint block
        0,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        600.0     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x000c9646947b1ea1cd3c33df8aeb38b19d840f2eb7ceb88da856770714c99c17"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1518608373,
        0,
        300
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x268c43be09de6fe7712cd25c219d29282f6e3e5f33f5e1a8b1bee1a131e39fbb"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0xa5;
        pchMessageStart[2] = 0x6b;
        pchMessageStart[3] = 0x69;
        vAlertPubKey = ParseHex("04f8ef0cb6cdc1da10d73690005f4bfab2dcffb81bc5de8d27da10da2c6d4ab1a81558892ce7244ba642a90894ba4bd661409f6431c42dcf9fa9eb2c2c450f314b");
        nDefaultPort = 9883;
        bnProofOfWorkLimit = ~uint256(0) >> 8;
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        nTargetSpacing = 10 * 60;
        nMaxTipAge = 24 * 60 * 60;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         */
        const char* pszTimestamp = "The Times 06/Feb/2018 Bitcoin is a Ponzi scheme, warns banker";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("042afc6d78ec20e5c6f77af79f802e908b0bdb0f2cdaf7e3d129dcc0e10a70f68f8e6cb6bcbdd6ea2931fb722f1f39be47005d17f031788b9eb652c875b195df24") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1550309875;
        genesis.nBits    = 0x2000ffff;
        genesis.nNonce   = 410;


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000e95d1e8959098cfafba9b4db3fe4ec98e7eb18c30dd14840bac1673fe204f"));
        assert(genesis.hashMerkleRoot == uint256("0xc3bbb18634caf9ccdf31409034aca72a72b0279e0fd27183c87b45ca9d05105f"));

        vSeeds.push_back(CDNSSeedData("ns.meowmeowcoin.com", "seeds.meowmeowcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(112);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(56);
        base58Prefixes[SECRET_KEY] =     list_of(224);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xA4)(0xC4);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xB4)(0xD4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0x76;
        pchMessageStart[3] = 0x75;
        vAlertPubKey = ParseHex("0409c18f47356ed1b996e72c587821a5a23ae58b83c032c3d67342627f471c6c2803953b37416a249adac43b5771ae913eae1351a33f82748ed33b696a81e48fbe");
        nDefaultPort = 19883;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 10 * 60;
        nMaxTipAge = 0x7fffffff;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1550309874;
        genesis.nNonce = 270;


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00f8d49159357b49a753c8aa97b21c9f67a88963a926daaac8e12e1dbd2c309c"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("alexykot.me", "testnet-seed.alexykot.me"));
        //vSeeds.push_back(CDNSSeedData("bitcoin.petertodd.org", "testnet-seed.bitcoin.petertodd.org"));
        //vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));
        //vSeeds.push_back(CDNSSeedData("bitcoin.schildbach.de", "testnet-seed.bitcoin.schildbach.de"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(110);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(55);
        base58Prefixes[SECRET_KEY]     = list_of(220);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0xA4)(0xC4);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0xB4)(0xD4);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0xca;
        pchMessageStart[2] = 0x87;
        pchMessageStart[3] = 0x81;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 10 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxTipAge = 24 * 60 * 60;
        genesis.nTime = 1550309873;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;


        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        assert(hashGenesisBlock == uint256("0x49027e937a3d6a2c9cffe0d0e4d5d30a230e53544df04f394047d1d08ab10b61"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
