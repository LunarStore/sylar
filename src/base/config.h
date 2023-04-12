/*******************************************
 * Author : Lunar 
 * Email: : 1981811204@qq.com 
 * CreateTime : 2023-01-27 13:06
 * LastModified : 2023-01-27 13:06
 * Filename : config.h
 * Description : 1.0 *
 ************************************/

#ifndef __LUNAR_CONFIG_H__

#define __LUNAR_CONFIG_H__



#include<memory>
#include<string>
#include<unordered_map>
#include<stdint.h>
#include <boost/lexical_cast.hpp>
#include<vector>
#include<list>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include <yaml-cpp/yaml.h>
#include<sstream>

#include"base/log.h"
#include"base/singleton.h"
#include"init/env.h"
#include"base/mutex.h"
#include"base/util.h"
namespace lunar{
    //static Logger::ptr g_logger = LUNAR_LOG_NAME("system");
    /**
     * @brief 类型转换模板类(F 源类型, T 目标类型)
     */

    //字符串转字符串!???
    template<typename F,typename T>
    class LexicalCast{
    public:
        T operator()(const F& val){
            return boost::lexical_cast<T>(val);
        }
    };


    /**
     * @brief 偏特化类型转换模板类YAMLString类型转化成vector<T>类型
     */
    template<typename T>
    class LexicalCast<std::string, std::vector<T> >{
    public:
        std::vector<T> operator()(const std::string& val){
            YAML::Node node = YAML::Load(val);
            std::vector<T> res;

            for(size_t i = 0; i < node.size(); i++){
                std::stringstream ss("");
                ss << node[i];
                res.push_back(LexicalCast<std::string, T>()(ss.str()));
            }
            return res;
        }
    };

    /**
     * @brief 偏特化类型转换，vector<T>类型转化成YAMLString类型
     */
    template<typename T>
    class LexicalCast<std::vector<T>, std::string>{
    public:
        std::string operator()(const std::vector<T>& val){
            //当前node 当成vector类型
            YAML::Node res;
            std::stringstream ss;
            for(size_t i = 0; i < val.size(); i++){
                YAML::Node node = YAML::Load(LexicalCast<T, std::string>()(val[i]));
                res.push_back(node);
            }
            ss << res;
            return ss.str();
        }
    };

        
    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::list<T>)
     */
    template<class T>
    class LexicalCast<std::string, std::list<T> > {
    public:
        std::list<T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::list<T> vec;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i) {
                ss.str("");
                ss << node[i];
                vec.push_back(LexicalCast<std::string, T>()(ss.str()));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::list<T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::list<T>, std::string> {
    public:
        std::string operator()(const std::list<T>& v) {
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto& i : v) {
                node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::set<T>)
     */
    template<class T>
    class LexicalCast<std::string, std::set<T> > {
    public:
        std::set<T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::set<T> vec;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i) {
                ss.str("");
                ss << node[i];
                vec.insert(LexicalCast<std::string, T>()(ss.str()));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::set<T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::set<T>, std::string> {
    public:
        std::string operator()(const std::set<T>& v) {
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto& i : v) {
                node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::unordered_set<T>)
     */
    template<class T>
    class LexicalCast<std::string, std::unordered_set<T> > {
    public:
        std::unordered_set<T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::unordered_set<T> vec;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i) {
                ss.str("");
                ss << node[i];
                vec.insert(LexicalCast<std::string, T>()(ss.str()));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::unordered_set<T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::unordered_set<T>, std::string> {
    public:
        std::string operator()(const std::unordered_set<T>& v) {
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto& i : v) {
                node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::map<std::string, T>)
     */
    template<class T>
    class LexicalCast<std::string, std::map<std::string, T> > {
    public:
        std::map<std::string, T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::map<std::string, T> vec;
            std::stringstream ss;
            for(auto it = node.begin();
                    it != node.end(); ++it) {
                ss.str("");
                ss << it->second;
                vec.insert(std::make_pair(it->first.Scalar(),
                            LexicalCast<std::string, T>()(ss.str())));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::map<std::string, T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::map<std::string, T>, std::string> {
    public:
        std::string operator()(const std::map<std::string, T>& v) {
            YAML::Node node(YAML::NodeType::Map);
            for(auto& i : v) {
                node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::unordered_map<std::string, T>)
     */
    template<class T>
    class LexicalCast<std::string, std::unordered_map<std::string, T> > {
    public:
        std::unordered_map<std::string, T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::unordered_map<std::string, T> vec;
            std::stringstream ss;
            for(auto it = node.begin();
                    it != node.end(); ++it) {
                ss.str("");
                ss << it->second;
                vec.insert(std::make_pair(it->first.Scalar(),
                            LexicalCast<std::string, T>()(ss.str())));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::unordered_map<std::string, T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::unordered_map<std::string, T>, std::string> {
    public:
        std::string operator()(const std::unordered_map<std::string, T>& v) {
            YAML::Node node(YAML::NodeType::Map);
            for(auto& i : v) {
                node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };


    class ConfigVarBase{
    public:
        typedef std::shared_ptr<ConfigVarBase> ptr;
        typedef RWMutex MutexType;
    public:
        ConfigVarBase(const std::string& name, 
            const std::string& description);
        virtual ~ConfigVarBase() {  };
    public:
        virtual std::string toString() = 0;

        virtual bool fromString(const std::string& val) = 0;


    public:
        const std::string& getName() const{ return m_name; }

        const std::string& getDescription() const{ return m_description; }
    protected:
        std::string m_name;
        std::string m_description;
        MutexType m_mutex;
    };

    template<typename T,
        typename ToStr = LexicalCast<T, std::string>,
        typename FromStr= LexicalCast<std::string, T> >
    class ConfigVar : public ConfigVarBase{
    public:
        typedef std::shared_ptr<ConfigVar<T, ToStr, FromStr>> ptr;

        typedef std::function<void(const T& /*oldVal*/, const T& /*newVal*/)> OnChangeCBType;
    public:
        ConfigVar(const T& val,
            const std::string& name,
            const std::string& description):ConfigVarBase(name, description),
            m_value(val){
        }

        virtual ~ConfigVar() override {  }
        virtual std::string toString() override{
            //需要处理boost::lexical_cast抛出的异常
            try{
                MutexType::ReadLock rlock(m_mutex);
                return ToStr()(m_value);
            }catch(std::exception& e){
                LUNAR_LOG_ERROR(LUNAR_LOG_NAME("system")) << "ConfigVar::toString exception:"
                    << " convert " << TypeToName<T>() << " to string "
                    << ",ConfigVar::m_name = " << m_name;
            }
            return "";
        }

        virtual bool fromString(const std::string& val) override{
            try{
                setValue(FromStr()(val));
                return true;
            }catch(std::exception& e){
                LUNAR_LOG_ERROR(LUNAR_LOG_NAME("system")) << "ConfigVar::fromString exception:"
                    << " convert " << " string to " << TypeToName<T>()
                    << ",ConfigVar::m_name = " << m_name;
            }
            return false;
        }

    public:
        std::string getTypeName() { return TypeToName<T>(); }
        void setValue(const T& val){
            MutexType::WriteLock wlock(m_mutex);
            if(m_value == val){
                return;
            }
            for(auto it = m_cbs.begin(); it != m_cbs.end(); it++){
                it->second(m_value, val);
            }

            m_value = val;
        }
        
        const T& getValue(){
            MutexType::ReadLock rlock(m_mutex);
            return m_value;
        }

        uint64_t addListener(OnChangeCBType cb){
            static uint64_t key = 0;
            MutexType::WriteLock wlock(m_mutex);
            key++;
            m_cbs[key] = cb;
            return key;
        }
        void delListener(uint32_t key){
            MutexType::WriteLock wlock(m_mutex);
            m_cbs.erase(key);
        }
        void clearListener(){
            MutexType::WriteLock wlock(m_mutex);
            m_cbs.clear();
        }
    private:
        T m_value;
        std::map<uint32_t, OnChangeCBType> m_cbs;
    };

    //ConfigVarBase Manager class
    class ConfigVarManager{
    public:
        typedef std::shared_ptr<ConfigVarManager> ptr;
        typedef std::unordered_map<std::string, ConfigVarBase::ptr> ConfigVarMapType;
        typedef RWMutex MutexType;
    public:
        template<typename T>
        typename ConfigVar<T>::ptr lookUp(const std::string& name, 
            const T& default_val, 
            std::string default_description){
            MutexType::WriteLock wlock(m_mutex);
            typename ConfigVar<T>::ptr res;
            auto cv = m_cvs.find(name);
            if(cv != m_cvs.end()){
                res = std::dynamic_pointer_cast<ConfigVar<T>> (cv->second);
                if(res){
                    return res;
                }else{
                    LUNAR_LOG_ERROR(LUNAR_LOG_NAME("system")) << "ConfigVarManager::lookUp( name = " + name + " , ...) exist but type not "
                        << TypeToName<T>() << " ,real type is " << res->getTypeName();
                    return nullptr;
                }
            }
            
            res.reset(new ConfigVar<T>(default_val, name, default_description));
            m_cvs.insert({name, ConfigVarBase::ptr(res)});
            return res;
        }
        void loadFromFile(const std::string& val);
        void loadFromConfDir(const std::string& path, bool force = true);
        ConfigVarBase::ptr lookUpConfigVarByName(const std::string& val);
    private:
        ConfigVarMapType m_cvs;
        MutexType m_mutex;
    };

    typedef Singleton<ConfigVarManager> ConfigVarMgr;

}


#endif