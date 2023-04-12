#include"base/config.h"


namespace lunar{

    ConfigVarBase::ConfigVarBase(const std::string& name, 
        const std::string& description): m_name(name),
        m_description(description){
    }

    static void __ListAllYamlNode(std::string prefix,
        const YAML::Node& node,
        std::vector<std::pair<std::string, YAML::Node>>& output){

        output.push_back(std::make_pair(prefix, node));

        if(node.IsMap()){
            for(auto it = node.begin(); it != node.end(); it++){
                __ListAllYamlNode((prefix.empty() ? prefix :prefix + ".") + it->first.Scalar(), it->second, output);
            }
        }
    }

    void ConfigVarManager::loadFromFile(const std::string& val){
        std::vector<std::pair<std::string, YAML::Node>> nodes;
        YAML::Node root = YAML::LoadFile(val);
        __ListAllYamlNode("", root, nodes);

        for(auto it = nodes.begin(); it != nodes.end(); it++){
            ConfigVarBase::ptr var = lookUpConfigVarByName(it->first);
            if(var != nullptr){
                std::stringstream ss("");
                ss << it->second;
                var->fromString(ss.str());
            }
        }
    }
    void ConfigVarManager::loadFromConfDir(const std::string& path, bool force) {
        std::string absoulte_path = lunar::EnvMgr::GetInstance()->getAbsolutePath(path);
        std::vector<std::string> files;
        FSUtil::ListAllFile(files, absoulte_path, ".yml");

        for(auto& i : files) {
            try {
                loadFromFile(i);
                LUNAR_LOG_INFO(LUNAR_LOG_NAME("system")) << "LoadConfFile file="
                    << i << " ok";
            } catch (...) {
                LUNAR_LOG_ERROR(LUNAR_LOG_NAME("system")) << "LoadConfFile file="
                    << i << " failed";
            }
        }
    }
    ConfigVarBase::ptr ConfigVarManager::lookUpConfigVarByName(const std::string& val){
        MutexType::ReadLock rlock(m_mutex);
        auto res = m_cvs.find(val);
        if(res == m_cvs.end()){
            return nullptr;
        }

        return res->second;
    }
}